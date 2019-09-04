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
struct ds_device {int /*<<< orphan*/ * ep; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 size_t EP_DATA_OUT ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_send_data(struct ds_device *dev, unsigned char *buf, int len)
{
	int count, err;

	count = 0;
	err = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, dev->ep[EP_DATA_OUT]), buf, len, &count, 1000);
	if (err < 0) {
		pr_err("Failed to write 1-wire data to ep0x%x: "
			"err=%d.\n", dev->ep[EP_DATA_OUT], err);
		return err;
	}

	return err;
}