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
typedef  int uint32_t ;
struct usb_hcd {int dummy; } ;
struct urb {int interval; int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {int bandwidth_allocated; int /*<<< orphan*/  bandwidth_int_reqs; int /*<<< orphan*/  bandwidth_isoc_reqs; } ;

/* Variables and functions */
 scalar_t__ PIPE_ISOCHRONOUS ; 
 TYPE_1__* hcd_to_bus (struct usb_hcd*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_bus_bandwidth(struct usb_hcd *hcd, uint32_t bw,
			       struct urb *urb)
{
	hcd_to_bus(hcd)->bandwidth_allocated -= bw / urb->interval;
	if (usb_pipetype(urb->pipe) == PIPE_ISOCHRONOUS) {
		hcd_to_bus(hcd)->bandwidth_isoc_reqs--;
	} else {
		hcd_to_bus(hcd)->bandwidth_int_reqs--;
	}
}