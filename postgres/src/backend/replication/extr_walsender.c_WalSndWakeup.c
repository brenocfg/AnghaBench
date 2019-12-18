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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * latch; } ;
typedef  TYPE_1__ WalSnd ;
struct TYPE_4__ {TYPE_1__* walsnds; } ;
typedef  int /*<<< orphan*/  Latch ;

/* Variables and functions */
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_2__* WalSndCtl ; 
 int max_wal_senders ; 

void
WalSndWakeup(void)
{
	int			i;

	for (i = 0; i < max_wal_senders; i++)
	{
		Latch	   *latch;
		WalSnd	   *walsnd = &WalSndCtl->walsnds[i];

		/*
		 * Get latch pointer with spinlock held, for the unlikely case that
		 * pointer reads aren't atomic (as they're 8 bytes).
		 */
		SpinLockAcquire(&walsnd->mutex);
		latch = walsnd->latch;
		SpinLockRelease(&walsnd->mutex);

		if (latch != NULL)
			SetLatch(latch);
	}
}