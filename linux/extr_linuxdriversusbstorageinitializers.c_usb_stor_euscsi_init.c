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
struct us_data {int /*<<< orphan*/  send_ctrl_pipe; } ;

/* Variables and functions */
 int HZ ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int usb_stor_control_msg (struct us_data*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

int usb_stor_euscsi_init(struct us_data *us)
{
	int result;

	usb_stor_dbg(us, "Attempting to init eUSCSI bridge...\n");
	result = usb_stor_control_msg(us, us->send_ctrl_pipe,
			0x0C, USB_RECIP_INTERFACE | USB_TYPE_VENDOR,
			0x01, 0x0, NULL, 0x0, 5 * HZ);
	usb_stor_dbg(us, "-- result is %d\n", result);

	return 0;
}