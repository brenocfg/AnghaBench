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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_8192C_END_ADDRESS ; 
 int /*<<< orphan*/  FW_8192C_START_ADDRESS ; 
 int MAX_USBCTRL_VENDORREQ_TIMES ; 
 int /*<<< orphan*/  REALTEK_USB_VENQT_READ ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 unsigned int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _usbctrl_vendorreq_sync_read(struct usb_device *udev, u8 request,
					u16 value, u16 index, void *pdata,
					u16 len)
{
	unsigned int pipe;
	int status;
	u8 reqtype;
	int vendorreq_times = 0;
	static int count;

	pipe = usb_rcvctrlpipe(udev, 0); /* read_in */
	reqtype =  REALTEK_USB_VENQT_READ;

	do {
		status = usb_control_msg(udev, pipe, request, reqtype, value,
					 index, pdata, len, 1000);
		if (status < 0) {
			/* firmware download is checksumed, don't retry */
			if ((value >= FW_8192C_START_ADDRESS &&
			    value <= FW_8192C_END_ADDRESS))
				break;
		} else {
			break;
		}
	} while (++vendorreq_times < MAX_USBCTRL_VENDORREQ_TIMES);

	if (status < 0 && count++ < 4)
		pr_err("reg 0x%x, usbctrl_vendorreq TimeOut! status:0x%x value=0x%x\n",
		       value, status, *(u32 *)pdata);
	return status;
}