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
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* dev; } ;
struct snd_usb_caiaqdev {unsigned char* ep1_out_buf; TYPE_1__ chip; } ;

/* Variables and functions */
 int EIO ; 
 int EP1_BUFSIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,unsigned char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

int snd_usb_caiaq_send_command(struct snd_usb_caiaqdev *cdev,
			       unsigned char command,
			       const unsigned char *buffer,
			       int len)
{
	int actual_len;
	struct usb_device *usb_dev = cdev->chip.dev;

	if (!usb_dev)
		return -EIO;

	if (len > EP1_BUFSIZE - 1)
		len = EP1_BUFSIZE - 1;

	if (buffer && len > 0)
		memcpy(cdev->ep1_out_buf+1, buffer, len);

	cdev->ep1_out_buf[0] = command;
	return usb_bulk_msg(usb_dev, usb_sndbulkpipe(usb_dev, 1),
			   cdev->ep1_out_buf, len+1, &actual_len, 200);
}