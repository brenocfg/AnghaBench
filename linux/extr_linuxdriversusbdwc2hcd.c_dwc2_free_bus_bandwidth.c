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
typedef  int u16 ;
struct usb_hcd {int dummy; } ;
struct usb_bus {int bandwidth_allocated; int /*<<< orphan*/  bandwidth_int_reqs; int /*<<< orphan*/  bandwidth_isoc_reqs; } ;
struct urb {int interval; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 scalar_t__ PIPE_ISOCHRONOUS ; 
 struct usb_bus* hcd_to_bus (struct usb_hcd*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc2_free_bus_bandwidth(struct usb_hcd *hcd, u16 bw,
				    struct urb *urb)
{
	struct usb_bus *bus = hcd_to_bus(hcd);

	if (urb->interval)
		bus->bandwidth_allocated -= bw / urb->interval;
	if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS)
		bus->bandwidth_isoc_reqs--;
	else
		bus->bandwidth_int_reqs--;
}