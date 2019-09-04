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
struct fotg210_qh {scalar_t__ unlink_cycle; struct fotg210_qh* unlink_next; } ;
struct fotg210_hcd {scalar_t__ rh_state; int intr_unlinking; scalar_t__ intr_unlink_cycle; struct fotg210_qh* intr_unlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_HRTIMER_UNLINK_INTR ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 int /*<<< orphan*/  end_unlink_intr (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fotg210_handle_intr_unlinks(struct fotg210_hcd *fotg210)
{
	bool stopped = (fotg210->rh_state < FOTG210_RH_RUNNING);

	/*
	 * Process all the QHs on the intr_unlink list that were added
	 * before the current unlink cycle began.  The list is in
	 * temporal order, so stop when we reach the first entry in the
	 * current cycle.  But if the root hub isn't running then
	 * process all the QHs on the list.
	 */
	fotg210->intr_unlinking = true;
	while (fotg210->intr_unlink) {
		struct fotg210_qh *qh = fotg210->intr_unlink;

		if (!stopped && qh->unlink_cycle == fotg210->intr_unlink_cycle)
			break;
		fotg210->intr_unlink = qh->unlink_next;
		qh->unlink_next = NULL;
		end_unlink_intr(fotg210, qh);
	}

	/* Handle remaining entries later */
	if (fotg210->intr_unlink) {
		fotg210_enable_event(fotg210, FOTG210_HRTIMER_UNLINK_INTR,
				true);
		++fotg210->intr_unlink_cycle;
	}
	fotg210->intr_unlinking = false;
}