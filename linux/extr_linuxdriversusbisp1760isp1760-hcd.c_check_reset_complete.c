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
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_PORTSC1 ; 
 int PORT_CONNECT ; 
 int PORT_OWNER ; 
 int PORT_PE ; 
 int PORT_RWC_BITS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_reset_complete(struct usb_hcd *hcd, int index,
		int port_status)
{
	if (!(port_status & PORT_CONNECT))
		return port_status;

	/* if reset finished and it's still not enabled -- handoff */
	if (!(port_status & PORT_PE)) {

		dev_info(hcd->self.controller,
					"port %d full speed --> companion\n",
					index + 1);

		port_status |= PORT_OWNER;
		port_status &= ~PORT_RWC_BITS;
		reg_write32(hcd->regs, HC_PORTSC1, port_status);

	} else
		dev_info(hcd->self.controller, "port %d high speed\n",
								index + 1);

	return port_status;
}