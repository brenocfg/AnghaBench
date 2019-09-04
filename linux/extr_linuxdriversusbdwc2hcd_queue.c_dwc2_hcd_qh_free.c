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
struct dwc2_qh {scalar_t__ dw_align_buf; scalar_t__ desc_list; int /*<<< orphan*/  dwc_tt; int /*<<< orphan*/  wait_timer; int /*<<< orphan*/  unreserve_timer; } ;
struct dwc2_hsotg {scalar_t__ unaligned_cache; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_do_unreserve (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_hcd_qh_free_ddma (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_host_put_tt_info (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dwc2_qh*) ; 
 int /*<<< orphan*/  kmem_cache_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dwc2_hcd_qh_free(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	/* Make sure any unreserve work is finished. */
	if (del_timer_sync(&qh->unreserve_timer)) {
		unsigned long flags;

		spin_lock_irqsave(&hsotg->lock, flags);
		dwc2_do_unreserve(hsotg, qh);
		spin_unlock_irqrestore(&hsotg->lock, flags);
	}

	/*
	 * We don't have the lock so we can safely wait until the wait timer
	 * finishes.  Of course, at this point in time we'd better have set
	 * wait_timer_active to false so if this timer was still pending it
	 * won't do anything anyway, but we want it to finish before we free
	 * memory.
	 */
	hrtimer_cancel(&qh->wait_timer);

	dwc2_host_put_tt_info(hsotg, qh->dwc_tt);

	if (qh->desc_list)
		dwc2_hcd_qh_free_ddma(hsotg, qh);
	else if (hsotg->unaligned_cache && qh->dw_align_buf)
		kmem_cache_free(hsotg->unaligned_cache, qh->dw_align_buf);

	kfree(qh);
}