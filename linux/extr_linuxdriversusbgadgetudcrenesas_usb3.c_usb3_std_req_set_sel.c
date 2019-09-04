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
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; } ;
struct renesas_usb3 {int /*<<< orphan*/  ep0_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_pipe0_internal_xfer (struct renesas_usb3*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_pipe0_set_sel_completion ; 
 int /*<<< orphan*/  usb3_to_dev (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb_req_to_usb3_req (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool usb3_std_req_set_sel(struct renesas_usb3 *usb3,
				 struct usb_ctrlrequest *ctrl)
{
	u16 w_length = le16_to_cpu(ctrl->wLength);

	if (w_length != 6)
		return true;	/* stall */

	dev_dbg(usb3_to_dev(usb3), "set_sel: req = %p\n",
		usb_req_to_usb3_req(usb3->ep0_req));
	usb3_pipe0_internal_xfer(usb3, NULL, 6, usb3_pipe0_set_sel_completion);

	return false;
}