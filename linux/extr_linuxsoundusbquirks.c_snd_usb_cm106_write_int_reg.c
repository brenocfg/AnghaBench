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
typedef  int u8 ;
typedef  int u16 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int /*<<< orphan*/  USB_REQ_SET_CONFIGURATION ; 
 int USB_TYPE_CLASS ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_cm106_write_int_reg(struct usb_device *dev, int reg, u16 value)
{
	u8 buf[4];
	buf[0] = 0x20;
	buf[1] = value & 0xff;
	buf[2] = (value >> 8) & 0xff;
	buf[3] = reg;
	return snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), USB_REQ_SET_CONFIGURATION,
			       USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			       0, 0, &buf, 4);
}