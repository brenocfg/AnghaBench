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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_serial {TYPE_1__* interface; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP210X_VENDOR_SPECIFIC ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int /*<<< orphan*/  cp210x_interface_num (struct usb_serial*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp210x_read_vendor_block(struct usb_serial *serial, u8 type, u16 val,
				    void *buf, int bufsize)
{
	void *dmabuf;
	int result;

	dmabuf = kmalloc(bufsize, GFP_KERNEL);
	if (!dmabuf)
		return -ENOMEM;

	result = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
				 CP210X_VENDOR_SPECIFIC, type, val,
				 cp210x_interface_num(serial), dmabuf, bufsize,
				 USB_CTRL_GET_TIMEOUT);
	if (result == bufsize) {
		memcpy(buf, dmabuf, bufsize);
		result = 0;
	} else {
		dev_err(&serial->interface->dev,
			"failed to get vendor val 0x%04x size %d: %d\n", val,
			bufsize, result);
		if (result >= 0)
			result = -EIO;
	}

	kfree(dmabuf);

	return result;
}