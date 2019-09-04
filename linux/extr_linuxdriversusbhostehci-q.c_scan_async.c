#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct ehci_qh* qh; } ;
struct ehci_qh {scalar_t__ qh_state; int /*<<< orphan*/  unlink_cycle; int /*<<< orphan*/  qtd_list; TYPE_3__ qh_next; } ;
struct ehci_hcd {scalar_t__ rh_state; int enabled_hrtimer_events; int /*<<< orphan*/  async_unlink_cycle; struct ehci_qh* qh_scan_next; TYPE_2__* async; } ;
struct TYPE_4__ {struct ehci_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EHCI_HRTIMER_ASYNC_UNLINKS ; 
 scalar_t__ EHCI_RH_RUNNING ; 
 scalar_t__ QH_STATE_LINKED ; 
 int /*<<< orphan*/  ehci_enable_event (struct ehci_hcd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int qh_completions (struct ehci_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  start_unlink_async (struct ehci_hcd*,struct ehci_qh*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void scan_async (struct ehci_hcd *ehci)
{
	struct ehci_qh		*qh;
	bool			check_unlinks_later = false;

	ehci->qh_scan_next = ehci->async->qh_next.qh;
	while (ehci->qh_scan_next) {
		qh = ehci->qh_scan_next;
		ehci->qh_scan_next = qh->qh_next.qh;

		/* clean any finished work for this qh */
		if (!list_empty(&qh->qtd_list)) {
			int temp;

			/*
			 * Unlinks could happen here; completion reporting
			 * drops the lock.  That's why ehci->qh_scan_next
			 * always holds the next qh to scan; if the next qh
			 * gets unlinked then ehci->qh_scan_next is adjusted
			 * in single_unlink_async().
			 */
			temp = qh_completions(ehci, qh);
			if (unlikely(temp)) {
				start_unlink_async(ehci, qh);
			} else if (list_empty(&qh->qtd_list)
					&& qh->qh_state == QH_STATE_LINKED) {
				qh->unlink_cycle = ehci->async_unlink_cycle;
				check_unlinks_later = true;
			}
		}
	}

	/*
	 * Unlink empty entries, reducing DMA usage as well
	 * as HCD schedule-scanning costs.  Delay for any qh
	 * we just scanned, there's a not-unusual case that it
	 * doesn't stay idle for long.
	 */
	if (check_unlinks_later && ehci->rh_state == EHCI_RH_RUNNING &&
			!(ehci->enabled_hrtimer_events &
				BIT(EHCI_HRTIMER_ASYNC_UNLINKS))) {
		ehci_enable_event(ehci, EHCI_HRTIMER_ASYNC_UNLINKS, true);
		++ehci->async_unlink_cycle;
	}
}