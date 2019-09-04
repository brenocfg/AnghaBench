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
struct ds_status {int dummy; } ;
struct ds_device {int /*<<< orphan*/  st_buf; int /*<<< orphan*/ * ep; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 size_t EP_STATUS ; 
 int /*<<< orphan*/  ds_dump_status (struct ds_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct ds_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ds_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_interrupt_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_recv_status(struct ds_device *dev, struct ds_status *st,
			  bool dump)
{
	int count, err;

	if (st)
		memset(st, 0, sizeof(*st));

	count = 0;
	err = usb_interrupt_msg(dev->udev,
				usb_rcvintpipe(dev->udev,
					       dev->ep[EP_STATUS]),
				dev->st_buf, sizeof(dev->st_buf),
				&count, 1000);
	if (err < 0) {
		pr_err("Failed to read 1-wire data from 0x%x: err=%d.\n",
		       dev->ep[EP_STATUS], err);
		return err;
	}

	if (dump)
		ds_dump_status(dev, dev->st_buf, count);

	if (st && count >= sizeof(*st))
		memcpy(st, dev->st_buf, sizeof(*st));

	return count;
}