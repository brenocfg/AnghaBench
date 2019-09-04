#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uhci_hcd {int rh_numports; int /*<<< orphan*/  is_stopped; int /*<<< orphan*/  rh_state; scalar_t__ resuming_ports; scalar_t__ port_c_suspend; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  UHCI_IS_STOPPED ; 
 int /*<<< orphan*/  UHCI_RH_RESET ; 
 scalar_t__ USBPORTSC1 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* uhci_to_hcd (struct uhci_hcd*) ; 
 int /*<<< orphan*/  uhci_writew (struct uhci_hcd*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void finish_reset(struct uhci_hcd *uhci)
{
	int port;

	/* HCRESET doesn't affect the Suspend, Reset, and Resume Detect
	 * bits in the port status and control registers.
	 * We have to clear them by hand.
	 */
	for (port = 0; port < uhci->rh_numports; ++port)
		uhci_writew(uhci, 0, USBPORTSC1 + (port * 2));

	uhci->port_c_suspend = uhci->resuming_ports = 0;
	uhci->rh_state = UHCI_RH_RESET;
	uhci->is_stopped = UHCI_IS_STOPPED;
	clear_bit(HCD_FLAG_POLL_RH, &uhci_to_hcd(uhci)->flags);
}