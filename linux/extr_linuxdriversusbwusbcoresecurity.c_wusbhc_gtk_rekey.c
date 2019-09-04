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
struct wusbhc {int /*<<< orphan*/  gtk_rekey_work; int /*<<< orphan*/  wq_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void wusbhc_gtk_rekey(struct wusbhc *wusbhc)
{
	/*
	 * We need to submit a URB to the downstream WUSB devices in order to
	 * change the group key.  This can't be done while holding the
	 * wusbhc->mutex since that is also taken in the urb_enqueue routine
	 * and will cause a deadlock.  Instead, queue a work item to do
	 * it when the lock is not held
	 */
	queue_work(wusbhc->wq_security, &wusbhc->gtk_rekey_work);
}