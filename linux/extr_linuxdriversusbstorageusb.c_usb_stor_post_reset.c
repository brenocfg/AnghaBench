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
struct usb_interface {int dummy; } ;
struct us_data {int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct us_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_stor_report_bus_reset (struct us_data*) ; 

int usb_stor_post_reset(struct usb_interface *iface)
{
	struct us_data *us = usb_get_intfdata(iface);

	/* Report the reset to the SCSI core */
	usb_stor_report_bus_reset(us);

	/*
	 * If any of the subdrivers implemented a reinitialization scheme,
	 * this is where the callback would be invoked.
	 */

	mutex_unlock(&us->dev_mutex);
	return 0;
}