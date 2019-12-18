#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pid; scalar_t__ state; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ WalSnd ;
struct TYPE_4__ {TYPE_1__* walsnds; } ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ WALSNDSTATE_STOPPING ; 
 TYPE_2__* WalSndCtl ; 
 int max_wal_senders ; 
 int /*<<< orphan*/  pg_usleep (long) ; 

void
WalSndWaitStopping(void)
{
	for (;;)
	{
		int			i;
		bool		all_stopped = true;

		for (i = 0; i < max_wal_senders; i++)
		{
			WalSnd	   *walsnd = &WalSndCtl->walsnds[i];

			SpinLockAcquire(&walsnd->mutex);

			if (walsnd->pid == 0)
			{
				SpinLockRelease(&walsnd->mutex);
				continue;
			}

			if (walsnd->state != WALSNDSTATE_STOPPING)
			{
				all_stopped = false;
				SpinLockRelease(&walsnd->mutex);
				break;
			}
			SpinLockRelease(&walsnd->mutex);
		}

		/* safe to leave if confirmation is done for all WAL senders */
		if (all_stopped)
			return;

		pg_usleep(10000L);		/* wait for 10 msec */
	}
}