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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ snd_usb_pipe_sanity_check (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_interrupt_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndintpipe (struct usb_device*,int) ; 

__attribute__((used)) static int snd_usb_motu_microbookii_communicate(struct usb_device *dev, u8 *buf,
						int buf_size, int *length)
{
	int err, actual_length;

	if (snd_usb_pipe_sanity_check(dev, usb_sndintpipe(dev, 0x01)))
		return -EINVAL;
	err = usb_interrupt_msg(dev, usb_sndintpipe(dev, 0x01), buf, *length,
				&actual_length, 1000);
	if (err < 0)
		return err;

	print_hex_dump(KERN_DEBUG, "MicroBookII snd: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, actual_length, false);

	memset(buf, 0, buf_size);

	if (snd_usb_pipe_sanity_check(dev, usb_rcvintpipe(dev, 0x82)))
		return -EINVAL;
	err = usb_interrupt_msg(dev, usb_rcvintpipe(dev, 0x82), buf, buf_size,
				&actual_length, 1000);
	if (err < 0)
		return err;

	print_hex_dump(KERN_DEBUG, "MicroBookII rcv: ", DUMP_PREFIX_NONE, 16, 1,
		       buf, actual_length, false);

	*length = actual_length;
	return 0;
}