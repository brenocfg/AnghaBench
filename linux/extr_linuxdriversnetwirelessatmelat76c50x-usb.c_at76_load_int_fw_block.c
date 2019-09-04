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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFU_DNLOAD ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at76_load_int_fw_block(struct usb_device *udev, int blockno,
				  void *block, int size)
{
	return usb_control_msg(udev, usb_sndctrlpipe(udev, 0), DFU_DNLOAD,
			       USB_TYPE_CLASS | USB_DIR_OUT |
			       USB_RECIP_INTERFACE, blockno, 0, block, size,
			       USB_CTRL_GET_TIMEOUT);
}