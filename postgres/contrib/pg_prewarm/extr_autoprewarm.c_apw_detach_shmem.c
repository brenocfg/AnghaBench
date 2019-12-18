#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pid_using_dumpfile; scalar_t__ bgworker_pid; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 void* InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 scalar_t__ MyProcPid ; 
 TYPE_1__* apw_state ; 

__attribute__((used)) static void
apw_detach_shmem(int code, Datum arg)
{
	LWLockAcquire(&apw_state->lock, LW_EXCLUSIVE);
	if (apw_state->pid_using_dumpfile == MyProcPid)
		apw_state->pid_using_dumpfile = InvalidPid;
	if (apw_state->bgworker_pid == MyProcPid)
		apw_state->bgworker_pid = InvalidPid;
	LWLockRelease(&apw_state->lock);
}