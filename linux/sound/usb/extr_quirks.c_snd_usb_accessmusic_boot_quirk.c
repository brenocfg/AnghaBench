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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_pipe_sanity_check (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_interrupt_msg (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (struct usb_device*,int) ; 

__attribute__((used)) static int snd_usb_accessmusic_boot_quirk(struct usb_device *dev)
{
	int err, actual_length;
	/* "midi send" enable */
	static const u8 seq[] = { 0x4e, 0x73, 0x52, 0x01 };
	void *buf;

	if (snd_usb_pipe_sanity_check(dev, usb_sndintpipe(dev, 0x05)))
		return -EINVAL;
	buf = kmemdup(seq, ARRAY_SIZE(seq), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	err = usb_interrupt_msg(dev, usb_sndintpipe(dev, 0x05), buf,
			ARRAY_SIZE(seq), &actual_length, 1000);
	kfree(buf);
	if (err < 0)
		return err;

	return 0;
}