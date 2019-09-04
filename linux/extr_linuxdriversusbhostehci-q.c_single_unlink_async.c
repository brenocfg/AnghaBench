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
struct TYPE_4__ {struct ehci_qh* qh; } ;
struct ehci_qh {TYPE_2__ qh_next; TYPE_1__* hw; int /*<<< orphan*/  unlink_node; int /*<<< orphan*/  qh_state; } ;
struct ehci_hcd {struct ehci_qh* qh_scan_next; struct ehci_qh* async; int /*<<< orphan*/  async_unlink; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  QH_STATE_UNLINK_WAIT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void single_unlink_async(struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	struct ehci_qh		*prev;

	/* Add to the end of the list of QHs waiting for the next IAAD */
	qh->qh_state = QH_STATE_UNLINK_WAIT;
	list_add_tail(&qh->unlink_node, &ehci->async_unlink);

	/* Unlink it from the schedule */
	prev = ehci->async;
	while (prev->qh_next.qh != qh)
		prev = prev->qh_next.qh;

	prev->hw->hw_next = qh->hw->hw_next;
	prev->qh_next = qh->qh_next;
	if (ehci->qh_scan_next == qh)
		ehci->qh_scan_next = qh->qh_next.qh;
}