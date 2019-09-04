#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int abort; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ dwc_waitq_t ;

/* Variables and functions */
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int splbio () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

void DWC_WAITQ_ABORT(dwc_waitq_t *wq)
{
	int ipl;

	simple_lock(&wq->lock);
	ipl = splbio();
	wq->abort = 1;
	wakeup(wq);
	splx(ipl);
	simple_unlock(&wq->lock);
}