#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbtmc_device_data {TYPE_1__* usb_dev; int /*<<< orphan*/  bulk_out; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int usb_clear_halt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbtmc_ioctl_clear_out_halt(struct usbtmc_device_data *data)
{
	int rv;

	rv = usb_clear_halt(data->usb_dev,
			    usb_sndbulkpipe(data->usb_dev, data->bulk_out));

	if (rv < 0) {
		dev_err(&data->usb_dev->dev, "usb_control_msg returned %d\n",
			rv);
		return rv;
	}
	return 0;
}