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
struct usb_ctrlrequest {int wValue; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb3_set_device_address (struct renesas_usb3*,int) ; 
 int /*<<< orphan*/  usb3_set_p0_con_for_no_data (struct renesas_usb3*) ; 

__attribute__((used)) static bool usb3_std_req_set_address(struct renesas_usb3 *usb3,
				     struct usb_ctrlrequest *ctrl)
{
	if (ctrl->wValue >= 128)
		return true;	/* stall */

	usb3_set_device_address(usb3, ctrl->wValue);
	usb3_set_p0_con_for_no_data(usb3);

	return false;
}