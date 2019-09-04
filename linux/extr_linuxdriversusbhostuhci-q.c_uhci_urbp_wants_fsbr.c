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
struct urb_priv {scalar_t__ fsbr; } ;
struct uhci_hcd {int fsbr_is_wanted; int /*<<< orphan*/  fsbr_timer; scalar_t__ fsbr_expiring; int /*<<< orphan*/  fsbr_is_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_fsbr_on (struct uhci_hcd*) ; 

__attribute__((used)) static void uhci_urbp_wants_fsbr(struct uhci_hcd *uhci, struct urb_priv *urbp)
{
	if (urbp->fsbr) {
		uhci->fsbr_is_wanted = 1;
		if (!uhci->fsbr_is_on)
			uhci_fsbr_on(uhci);
		else if (uhci->fsbr_expiring) {
			uhci->fsbr_expiring = 0;
			del_timer(&uhci->fsbr_timer);
		}
	}
}