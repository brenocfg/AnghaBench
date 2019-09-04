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
 int usb_bulk_msg (struct usb_device*,unsigned int,void*,int,int*,int) ; 

int usb_interrupt_msg(struct usb_device *usb_dev, unsigned int pipe,
		      void *data, int len, int *actual_length, int timeout)
{
	return usb_bulk_msg(usb_dev, pipe, data, len, actual_length, timeout);
}