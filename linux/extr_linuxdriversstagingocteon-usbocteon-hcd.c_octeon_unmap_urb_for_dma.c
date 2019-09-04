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
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_free_temp_buffer (struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static void octeon_unmap_urb_for_dma(struct usb_hcd *hcd, struct urb *urb)
{
	usb_hcd_unmap_urb_for_dma(hcd, urb);
	octeon_free_temp_buffer(urb);
}