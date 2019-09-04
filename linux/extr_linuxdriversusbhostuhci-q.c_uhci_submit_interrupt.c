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
struct urb {int interval; } ;
struct uhci_qh {int period; int phase; int /*<<< orphan*/  bandwidth_reserved; int /*<<< orphan*/  skel; } ;
struct uhci_hcd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_PHASE ; 
 int /*<<< orphan*/  SKEL_INDEX (int) ; 
 int uhci_check_bandwidth (struct uhci_hcd*,struct uhci_qh*) ; 
 int /*<<< orphan*/  uhci_reserve_bandwidth (struct uhci_hcd*,struct uhci_qh*) ; 
 int uhci_submit_common (struct uhci_hcd*,struct urb*,struct uhci_qh*) ; 

__attribute__((used)) static int uhci_submit_interrupt(struct uhci_hcd *uhci, struct urb *urb,
		struct uhci_qh *qh)
{
	int ret;

	/* USB 1.1 interrupt transfers only involve one packet per interval.
	 * Drivers can submit URBs of any length, but longer ones will need
	 * multiple intervals to complete.
	 */

	if (!qh->bandwidth_reserved) {
		int exponent;

		/* Figure out which power-of-two queue to use */
		for (exponent = 7; exponent >= 0; --exponent) {
			if ((1 << exponent) <= urb->interval)
				break;
		}
		if (exponent < 0)
			return -EINVAL;

		/* If the slot is full, try a lower period */
		do {
			qh->period = 1 << exponent;
			qh->skel = SKEL_INDEX(exponent);

			/* For now, interrupt phase is fixed by the layout
			 * of the QH lists.
			 */
			qh->phase = (qh->period / 2) & (MAX_PHASE - 1);
			ret = uhci_check_bandwidth(uhci, qh);
		} while (ret != 0 && --exponent >= 0);
		if (ret)
			return ret;
	} else if (qh->period > urb->interval)
		return -EINVAL;		/* Can't decrease the period */

	ret = uhci_submit_common(uhci, urb, qh);
	if (ret == 0) {
		urb->interval = qh->period;
		if (!qh->bandwidth_reserved)
			uhci_reserve_bandwidth(uhci, qh);
	}
	return ret;
}