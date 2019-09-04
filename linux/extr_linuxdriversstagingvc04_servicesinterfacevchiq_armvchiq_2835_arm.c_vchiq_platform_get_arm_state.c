#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vchiq_2835_state {int /*<<< orphan*/  arm_state; int /*<<< orphan*/  inited; } ;
struct TYPE_3__ {scalar_t__ platform_state; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
typedef  int /*<<< orphan*/  VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

VCHIQ_ARM_STATE_T*
vchiq_platform_get_arm_state(VCHIQ_STATE_T *state)
{
	struct vchiq_2835_state *platform_state;

	platform_state   = (struct vchiq_2835_state *)state->platform_state;

	WARN_ON_ONCE(!platform_state->inited);

	return &platform_state->arm_state;
}