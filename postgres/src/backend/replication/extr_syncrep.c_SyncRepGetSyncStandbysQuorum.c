#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ WalSndState ;
struct TYPE_5__ {int pid; scalar_t__ state; scalar_t__ sync_standby_priority; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flush; } ;
typedef  TYPE_1__ WalSnd ;
struct TYPE_7__ {scalar_t__ syncrep_method; } ;
struct TYPE_6__ {TYPE_1__* walsnds; } ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__ volatile* MyWalSnd ; 
 int /*<<< orphan*/ * NIL ; 
 scalar_t__ SYNC_REP_QUORUM ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_3__* SyncRepConfig ; 
 scalar_t__ WALSNDSTATE_STOPPING ; 
 scalar_t__ WALSNDSTATE_STREAMING ; 
 TYPE_2__* WalSndCtl ; 
 scalar_t__ XLogRecPtrIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend_int (int /*<<< orphan*/ *,int) ; 
 int max_wal_senders ; 

__attribute__((used)) static List *
SyncRepGetSyncStandbysQuorum(bool *am_sync)
{
	List	   *result = NIL;
	int			i;
	volatile WalSnd *walsnd;	/* Use volatile pointer to prevent code
								 * rearrangement */

	Assert(SyncRepConfig->syncrep_method == SYNC_REP_QUORUM);

	for (i = 0; i < max_wal_senders; i++)
	{
		XLogRecPtr	flush;
		WalSndState state;
		int			pid;

		walsnd = &WalSndCtl->walsnds[i];

		SpinLockAcquire(&walsnd->mutex);
		pid = walsnd->pid;
		flush = walsnd->flush;
		state = walsnd->state;
		SpinLockRelease(&walsnd->mutex);

		/* Must be active */
		if (pid == 0)
			continue;

		/* Must be streaming or stopping */
		if (state != WALSNDSTATE_STREAMING &&
			state != WALSNDSTATE_STOPPING)
			continue;

		/* Must be synchronous */
		if (walsnd->sync_standby_priority == 0)
			continue;

		/* Must have a valid flush position */
		if (XLogRecPtrIsInvalid(flush))
			continue;

		/*
		 * Consider this standby as a candidate for quorum sync standbys and
		 * append it to the result.
		 */
		result = lappend_int(result, i);
		if (am_sync != NULL && walsnd == MyWalSnd)
			*am_sync = true;
	}

	return result;
}