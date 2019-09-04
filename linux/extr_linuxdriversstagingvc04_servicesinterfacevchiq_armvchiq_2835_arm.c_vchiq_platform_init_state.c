#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vchiq_2835_state {int inited; int /*<<< orphan*/  arm_state; } ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_4__ {scalar_t__ platform_state; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VCHIQ_SUCCESS ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vchiq_arm_init_state (TYPE_1__*,int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T
vchiq_platform_init_state(VCHIQ_STATE_T *state)
{
	VCHIQ_STATUS_T status = VCHIQ_SUCCESS;
	struct vchiq_2835_state *platform_state;

	state->platform_state = kzalloc(sizeof(*platform_state), GFP_KERNEL);
	platform_state = (struct vchiq_2835_state *)state->platform_state;

	platform_state->inited = 1;
	status = vchiq_arm_init_state(state, &platform_state->arm_state);

	if (status != VCHIQ_SUCCESS)
		platform_state->inited = 0;

	return status;
}