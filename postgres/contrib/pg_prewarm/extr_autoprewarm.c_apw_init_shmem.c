#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tranche; } ;
struct TYPE_4__ {TYPE_3__ lock; void* pid_using_dumpfile; void* bgworker_pid; } ;
typedef  int /*<<< orphan*/  AutoPrewarmSharedState ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 void* InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockInitialize (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockNewTrancheId () ; 
 int /*<<< orphan*/  LWLockRegisterTranche (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* ShmemInitStruct (char*,int,int*) ; 
 TYPE_1__* apw_state ; 

__attribute__((used)) static bool
apw_init_shmem(void)
{
	bool		found;

	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);
	apw_state = ShmemInitStruct("autoprewarm",
								sizeof(AutoPrewarmSharedState),
								&found);
	if (!found)
	{
		/* First time through ... */
		LWLockInitialize(&apw_state->lock, LWLockNewTrancheId());
		apw_state->bgworker_pid = InvalidPid;
		apw_state->pid_using_dumpfile = InvalidPid;
	}
	LWLockRelease(AddinShmemInitLock);

	LWLockRegisterTranche(apw_state->lock.tranche, "autoprewarm");

	return found;
}