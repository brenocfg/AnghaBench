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
struct oxu_hcd {int dummy; } ;
struct ehci_qh {int hw_info2; int /*<<< orphan*/  hw_next; int /*<<< orphan*/  qh_state; int /*<<< orphan*/  qtd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_LIST_END ; 
 int /*<<< orphan*/  QH_CMASK ; 
 int /*<<< orphan*/  QH_STATE_IDLE ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qh_unlink_periodic (struct oxu_hcd*,struct ehci_qh*) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void intr_deschedule(struct oxu_hcd *oxu, struct ehci_qh *qh)
{
	unsigned wait;

	qh_unlink_periodic(oxu, qh);

	/* simple/paranoid:  always delay, expecting the HC needs to read
	 * qh->hw_next or finish a writeback after SPLIT/CSPLIT ... and
	 * expect hub_wq to clean up after any CSPLITs we won't issue.
	 * active high speed queues may need bigger delays...
	 */
	if (list_empty(&qh->qtd_list)
		|| (cpu_to_le32(QH_CMASK) & qh->hw_info2) != 0)
		wait = 2;
	else
		wait = 55;	/* worst case: 3 * 1024 */

	udelay(wait);
	qh->qh_state = QH_STATE_IDLE;
	qh->hw_next = EHCI_LIST_END;
	wmb();
}