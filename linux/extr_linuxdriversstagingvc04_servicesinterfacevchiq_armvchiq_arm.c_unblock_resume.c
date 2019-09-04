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
struct TYPE_3__ {scalar_t__ resume_blocked; int /*<<< orphan*/  resume_blocker; } ;
typedef  TYPE_1__ VCHIQ_ARM_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
unblock_resume(VCHIQ_ARM_STATE_T *arm_state)
{
	complete_all(&arm_state->resume_blocker);
	arm_state->resume_blocked = 0;
}