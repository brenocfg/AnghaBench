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
typedef  int /*<<< orphan*/  BgWorkerStartTime ;

/* Variables and functions */
 int /*<<< orphan*/  BgWorkerStart_ConsistentState ; 
 int /*<<< orphan*/  BgWorkerStart_PostmasterStart ; 
 int /*<<< orphan*/  BgWorkerStart_RecoveryFinished ; 
#define  PM_HOT_STANDBY 139 
#define  PM_INIT 138 
#define  PM_NO_CHILDREN 137 
#define  PM_RECOVERY 136 
#define  PM_RUN 135 
#define  PM_SHUTDOWN 134 
#define  PM_SHUTDOWN_2 133 
#define  PM_STARTUP 132 
#define  PM_WAIT_BACKENDS 131 
#define  PM_WAIT_BACKUP 130 
#define  PM_WAIT_DEAD_END 129 
#define  PM_WAIT_READONLY 128 
 int pmState ; 

__attribute__((used)) static bool
bgworker_should_start_now(BgWorkerStartTime start_time)
{
	switch (pmState)
	{
		case PM_NO_CHILDREN:
		case PM_WAIT_DEAD_END:
		case PM_SHUTDOWN_2:
		case PM_SHUTDOWN:
		case PM_WAIT_BACKENDS:
		case PM_WAIT_READONLY:
		case PM_WAIT_BACKUP:
			break;

		case PM_RUN:
			if (start_time == BgWorkerStart_RecoveryFinished)
				return true;
			/* fall through */

		case PM_HOT_STANDBY:
			if (start_time == BgWorkerStart_ConsistentState)
				return true;
			/* fall through */

		case PM_RECOVERY:
		case PM_STARTUP:
		case PM_INIT:
			if (start_time == BgWorkerStart_PostmasterStart)
				return true;
			/* fall through */

	}

	return false;
}