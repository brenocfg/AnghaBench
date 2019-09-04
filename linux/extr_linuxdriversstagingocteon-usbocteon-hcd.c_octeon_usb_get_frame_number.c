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
struct octeon_hcd {int dummy; } ;

/* Variables and functions */
 int cvmx_usb_get_frame_number (struct octeon_hcd*) ; 
 struct octeon_hcd* hcd_to_octeon (struct usb_hcd*) ; 

__attribute__((used)) static int octeon_usb_get_frame_number(struct usb_hcd *hcd)
{
	struct octeon_hcd *usb = hcd_to_octeon(hcd);

	return cvmx_usb_get_frame_number(usb);
}