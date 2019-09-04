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
 size_t EP_DATA_IN ; 
 int /*<<< orphan*/  ds_recv_status (struct ds_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_recv_data(struct ds_device *dev, unsigned char *buf, int size)
{
	int count, err;

	/* Careful on size.  If size is less than what is available in
	 * the input buffer, the device fails the bulk transfer and
	 * clears the input buffer.  It could read the maximum size of
	 * the data buffer, but then do you return the first, last, or
	 * some set of the middle size bytes?  As long as the rest of
	 * the code is correct there will be size bytes waiting.  A
	 * call to ds_wait_status will wait until the device is idle
	 * and any data to be received would have been available.
	 */
	count = 0;
	err = usb_bulk_msg(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]),
				buf, size, &count, 1000);
	if (err < 0) {
		pr_info("Clearing ep0x%x.\n", dev->ep[EP_DATA_IN]);
		usb_clear_halt(dev->udev, usb_rcvbulkpipe(dev->udev, dev->ep[EP_DATA_IN]));
		ds_recv_status(dev, NULL, true);
		return err;
	}

#if 0
	{
		int i;

		printk("%s: count=%d: ", __func__, count);
		for (i = 0; i < count; ++i)
			printk("%02x ", buf[i]);
		printk("\n");
	}
#endif
	return count;
}