/*
 *
 *
 *  Created on: 2014-6-3
 *      Author: scott.cgi
 */

#ifndef physics_body_h
#define physics_body_h

#include "Mojoc/Toolkit/Math/Matrix.h"
#include "Mojoc/Toolkit/Define/Bitwise.h"
#include "Mojoc/Toolkit/Utils/Array.h"


typedef enum
{
	physics_shape_polygon = 1,
	physics_shape_line    = 1 << 2,
	physics_shape_point   = 1 << 3,
	physics_shape_length,
}
PhysicsShape;

/**
 * If contains 'is' the state can set and clear
 * else the state will automatically set and clear
 */
typedef enum
{
	physics_body_state_null           = 0,

	/** Auto set no motion can collision, collision will wake up */
	physics_body_state_sleeping       = 1,

	/** Auto set whether has collision */
	physics_body_state_collision      = 1 << 1,

//--------------------------------------------------------------------------------------------------

	/** No motion can collision */
	physics_body_state_is_fixed       = 1 << 2,

	/** No motion no collision forever */
	physics_body_state_is_freeze      = 1 << 3,


//--------------------------------------------------------------------------------------------------


	physics_body_state_no_motion      = physics_body_state_sleeping  |
								        physics_body_state_is_fixed  |
								        physics_body_state_is_freeze,

   physics_body_state_no_collision    = physics_body_state_is_freeze,

}
PhysicsBodyState;


/**
 * Recommended cache and reused
 */
typedef struct PhysicsBody PhysicsBody;
struct  PhysicsBody
{
	/** Bind data can not get from context */
	void*            userData;
	/** Default -1 used to identify PhysicsBody*/
	int              userId;

	float            positionX;
	float            positionY;
	float            velocityX;
	float            velocityY;
	float            accelerationX;
	float            accelerationY;
	float            rotationZ;

	PhysicsShape     shape;
	Array(float)     vertexArr  [1];
	/** The vertices after transformed */
	Array(float)     positionArr[1];
	int              state;

	/**
	 * Pow of 2, default 0
	 * body can collision between different collisionGroup
	 */
	int              collisionGroup;

	void (*OnCollision)(PhysicsBody* self, PhysicsBody* other, float deltaTime);
};


struct APhysicsBody
{
	/**
	 * Create body with shape by vertices
	 * if shape not support will return NULL
	 */
	PhysicsBody* (*Create)      (PhysicsShape shape, Array(float)* vertexArr);

	/**
	 * Update body shape motion
	 */
	void         (*UpdateMotion)(PhysicsBody* body, float deltaTime);

};

extern struct APhysicsBody APhysicsBody[1];


static inline bool APhysicsBodyCheckState(PhysicsBody* physicsBody, PhysicsBodyState checkState)
{
	return ABitwiseCheck(physicsBody->state, checkState);
}


static inline void APhysicsBodySetState(PhysicsBody* physicsBody, PhysicsBodyState setState)
{
	ABitwiseSet(physicsBody->state, setState);
}


static inline void APhysicsBodySetOnlyState(PhysicsBody* physicsBody, PhysicsBodyState setOnlyState)
{
	ABitwiseSetOnly(physicsBody->state, setOnlyState);
}


static inline void APhysicsBodyClearState(PhysicsBody* physicsBody, PhysicsBodyState clearState)
{
	ABitwiseClear(physicsBody->state, clearState);
}


static inline void APhysicsBodyClearAndSetState(PhysicsBody* physicsBody, PhysicsBodyState clearState, PhysicsBodyState setState)
{
	ABitwiseClearAndSet(physicsBody->state, clearState, setState);
}


//--------------------------------------------------------------------------------------------------


static inline bool APhysicsBodyCheckCollisionGroup(PhysicsBody* physicsBody,  int checkCollisionGroup)
{
	return ABitwiseCheck(physicsBody->collisionGroup, checkCollisionGroup);
}


static inline void APhysicsBodySetCollisionGroup(PhysicsBody* physicsBody,    int setCollisionGroup)
{
	ABitwiseSet(physicsBody->collisionGroup, setCollisionGroup);
}


static inline void APhysicsBodySetOnlyCollisionGroup(PhysicsBody* physicsBody, int setOnlycollisionGroup)
{
	ABitwiseSetOnly(physicsBody->collisionGroup, setOnlycollisionGroup);
}


static inline void APhysicsBodyClearCollisionGroup(PhysicsBody* physicsBody,   int clearCollisionGroup)
{
	ABitwiseClear(physicsBody->collisionGroup, clearCollisionGroup);
}

#endif
