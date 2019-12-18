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
typedef  enum rfkill_sched_op { ____Placeholder_rfkill_sched_op } rfkill_sched_op ;

/* Variables and functions */
 unsigned int NUM_RFKILL_TYPES ; 
#define  RFKILL_GLOBAL_OP_EPO 131 
#define  RFKILL_GLOBAL_OP_RESTORE 130 
#define  RFKILL_GLOBAL_OP_UNBLOCK 129 
#define  RFKILL_GLOBAL_OP_UNLOCK 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  rfkill_epo () ; 
 int /*<<< orphan*/  rfkill_remove_epo_lock () ; 
 int /*<<< orphan*/  rfkill_restore_states () ; 
 int /*<<< orphan*/  rfkill_switch_all (unsigned int,int) ; 

__attribute__((used)) static void __rfkill_handle_global_op(enum rfkill_sched_op op)
{
	unsigned int i;

	switch (op) {
	case RFKILL_GLOBAL_OP_EPO:
		rfkill_epo();
		break;
	case RFKILL_GLOBAL_OP_RESTORE:
		rfkill_restore_states();
		break;
	case RFKILL_GLOBAL_OP_UNLOCK:
		rfkill_remove_epo_lock();
		break;
	case RFKILL_GLOBAL_OP_UNBLOCK:
		rfkill_remove_epo_lock();
		for (i = 0; i < NUM_RFKILL_TYPES; i++)
			rfkill_switch_all(i, false);
		break;
	default:
		/* memory corruption or bug, fail safely */
		rfkill_epo();
		WARN(1, "Unknown requested operation %d! "
			"rfkill Emergency Power Off activated\n",
			op);
	}
}