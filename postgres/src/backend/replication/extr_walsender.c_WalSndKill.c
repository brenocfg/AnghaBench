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
struct TYPE_3__ {int /*<<< orphan*/  mutex; scalar_t__ pid; int /*<<< orphan*/ * latch; } ;
typedef  TYPE_1__ WalSnd ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
WalSndKill(int code, Datum arg)
{
	WalSnd	   *walsnd = MyWalSnd;

	Assert(walsnd != NULL);

	MyWalSnd = NULL;

	SpinLockAcquire(&walsnd->mutex);
	/* clear latch while holding the spinlock, so it can safely be read */
	walsnd->latch = NULL;
	/* Mark WalSnd struct as no longer being in use. */
	walsnd->pid = 0;
	SpinLockRelease(&walsnd->mutex);
}