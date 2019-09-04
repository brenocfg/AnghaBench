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
struct timer_list {int dummy; } ;
struct dwc2_qh {scalar_t__ unreserve_pending; int /*<<< orphan*/  unreserve_timer; struct dwc2_hsotg* hsotg; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_do_unreserve (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 struct dwc2_qh* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct dwc2_qh* qh ; 
 int /*<<< orphan*/  spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unreserve_timer ; 

__attribute__((used)) static void dwc2_unreserve_timer_fn(struct timer_list *t)
{
	struct dwc2_qh *qh = from_timer(qh, t, unreserve_timer);
	struct dwc2_hsotg *hsotg = qh->hsotg;
	unsigned long flags;

	/*
	 * Wait for the lock, or for us to be scheduled again.  We
	 * could be scheduled again if:
	 * - We started executing but didn't get the lock yet.
	 * - A new reservation came in, but cancel didn't take effect
	 *   because we already started executing.
	 * - The timer has been kicked again.
	 * In that case cancel and wait for the next call.
	 */
	while (!spin_trylock_irqsave(&hsotg->lock, flags)) {
		if (timer_pending(&qh->unreserve_timer))
			return;
	}

	/*
	 * Might be no more unreserve pending if:
	 * - We started executing but didn't get the lock yet.
	 * - A new reservation came in, but cancel didn't take effect
	 *   because we already started executing.
	 *
	 * We can't put this in the loop above because unreserve_pending needs
	 * to be accessed under lock, so we can only check it once we got the
	 * lock.
	 */
	if (qh->unreserve_pending)
		dwc2_do_unreserve(hsotg, qh);

	spin_unlock_irqrestore(&hsotg->lock, flags);
}