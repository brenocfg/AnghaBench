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
struct TYPE_3__ {int SharedRecoveryInProgress; } ;
typedef  TYPE_1__ XLogCtlData ;

/* Variables and functions */
 int /*<<< orphan*/  InitXLOGAccess () ; 
 int LocalRecoveryInProgress ; 
 TYPE_1__* XLogCtl ; 
 int /*<<< orphan*/  pg_memory_barrier () ; 

bool
RecoveryInProgress(void)
{
	/*
	 * We check shared state each time only until we leave recovery mode. We
	 * can't re-enter recovery, so there's no need to keep checking after the
	 * shared variable has once been seen false.
	 */
	if (!LocalRecoveryInProgress)
		return false;
	else
	{
		/*
		 * use volatile pointer to make sure we make a fresh read of the
		 * shared variable.
		 */
		volatile XLogCtlData *xlogctl = XLogCtl;

		LocalRecoveryInProgress = xlogctl->SharedRecoveryInProgress;

		/*
		 * Initialize TimeLineID and RedoRecPtr when we discover that recovery
		 * is finished. InitPostgres() relies upon this behaviour to ensure
		 * that InitXLOGAccess() is called at backend startup.  (If you change
		 * this, see also LocalSetXLogInsertAllowed.)
		 */
		if (!LocalRecoveryInProgress)
		{
			/*
			 * If we just exited recovery, make sure we read TimeLineID and
			 * RedoRecPtr after SharedRecoveryInProgress (for machines with
			 * weak memory ordering).
			 */
			pg_memory_barrier();
			InitXLOGAccess();
		}

		/*
		 * Note: We don't need a memory barrier when we're still in recovery.
		 * We might exit recovery immediately after return, so the caller
		 * can't rely on 'true' meaning that we're still in recovery anyway.
		 */

		return LocalRecoveryInProgress;
	}
}