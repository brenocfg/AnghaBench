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
 int /*<<< orphan*/  COMM_EP ; 
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 int usb_interrupt_msg (struct usb_device*,int /*<<< orphan*/ ,int*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb6fire_comm_send_buffer(u8 *buffer, struct usb_device *dev)
{
	int ret;
	int actual_len;

	ret = usb_interrupt_msg(dev, usb_sndintpipe(dev, COMM_EP),
			buffer, buffer[1] + 2, &actual_len, HZ);
	if (ret < 0)
		return ret;
	else if (actual_len != buffer[1] + 2)
		return -EIO;
	return 0;
}