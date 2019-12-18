#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  RFKILL_GLOBAL_OP_EPO ; 
 int /*<<< orphan*/  rfkill_master_switch_op ; 
 int /*<<< orphan*/  rfkill_schedule_global_op (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfkill_schedule_evsw_rfkillall(int state)
{
	if (state)
		rfkill_schedule_global_op(rfkill_master_switch_op);
	else
		rfkill_schedule_global_op(RFKILL_GLOBAL_OP_EPO);
}