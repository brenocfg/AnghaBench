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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int USB_CTRL_GET_TIMEOUT ; 
 int USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_ctl_msg_quirk (struct usb_device*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_pipe_sanity_check (struct usb_device*,unsigned int) ; 
 int usb_control_msg (struct usb_device*,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 

int snd_usb_ctl_msg(struct usb_device *dev, unsigned int pipe, __u8 request,
		    __u8 requesttype, __u16 value, __u16 index, void *data,
		    __u16 size)
{
	int err;
	void *buf = NULL;
	int timeout;

	if (snd_usb_pipe_sanity_check(dev, pipe))
		return -EINVAL;

	if (size > 0) {
		buf = kmemdup(data, size, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
	}

	if (requesttype & USB_DIR_IN)
		timeout = USB_CTRL_GET_TIMEOUT;
	else
		timeout = USB_CTRL_SET_TIMEOUT;

	err = usb_control_msg(dev, pipe, request, requesttype,
			      value, index, buf, size, timeout);

	if (size > 0) {
		memcpy(data, buf, size);
		kfree(buf);
	}

	snd_usb_ctl_msg_quirk(dev, pipe, request, requesttype,
			      value, index, data, size);

	return err;
}