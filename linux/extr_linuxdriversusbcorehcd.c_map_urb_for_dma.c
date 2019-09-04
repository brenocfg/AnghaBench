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
struct usb_hcd {TYPE_1__* driver; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int (* map_urb_for_dma ) (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int usb_hcd_map_urb_for_dma (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_urb_for_dma(struct usb_hcd *hcd, struct urb *urb,
			   gfp_t mem_flags)
{
	if (hcd->driver->map_urb_for_dma)
		return hcd->driver->map_urb_for_dma(hcd, urb, mem_flags);
	else
		return usb_hcd_map_urb_for_dma(hcd, urb, mem_flags);
}