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
struct uhci_hcd {int rh_numports; int /*<<< orphan*/  port_c_suspend; } ;

/* Variables and functions */
 int RWC_BITS ; 
 scalar_t__ USBPORTSC1 ; 
 int USBPORTSC_CCS ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int uhci_readw (struct uhci_hcd*,scalar_t__) ; 

__attribute__((used)) static int any_ports_active(struct uhci_hcd *uhci)
{
	int port;

	for (port = 0; port < uhci->rh_numports; ++port) {
		if ((uhci_readw(uhci, USBPORTSC1 + port * 2) &
				(USBPORTSC_CCS | RWC_BITS)) ||
				test_bit(port, &uhci->port_c_suspend))
			return 1;
	}
	return 0;
}