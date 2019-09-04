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
struct fotg210_qh_hw {int /*<<< orphan*/  hw_next; } ;
struct fotg210_qh {int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  qh_state; struct fotg210_qh_hw* hw; } ;
struct fotg210_hcd {scalar_t__ rh_state; int /*<<< orphan*/  intr_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_LIST_END (struct fotg210_hcd*) ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 int /*<<< orphan*/  QH_STATE_IDLE ; 
 int /*<<< orphan*/  disable_periodic (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_err (struct fotg210_hcd*,char*,struct fotg210_qh*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_completions (struct fotg210_hcd*,struct fotg210_qh*) ; 
 int qh_schedule (struct fotg210_hcd*,struct fotg210_qh*) ; 

__attribute__((used)) static void end_unlink_intr(struct fotg210_hcd *fotg210, struct fotg210_qh *qh)
{
	struct fotg210_qh_hw *hw = qh->hw;
	int rc;

	qh->qh_state = QH_STATE_IDLE;
	hw->hw_next = FOTG210_LIST_END(fotg210);

	qh_completions(fotg210, qh);

	/* reschedule QH iff another request is queued */
	if (!list_empty(&qh->qtd_list) &&
			fotg210->rh_state == FOTG210_RH_RUNNING) {
		rc = qh_schedule(fotg210, qh);

		/* An error here likely indicates handshake failure
		 * or no space left in the schedule.  Neither fault
		 * should happen often ...
		 *
		 * FIXME kill the now-dysfunctional queued urbs
		 */
		if (rc != 0)
			fotg210_err(fotg210, "can't reschedule qh %p, err %d\n",
					qh, rc);
	}

	/* maybe turn off periodic schedule */
	--fotg210->intr_count;
	disable_periodic(fotg210);
}