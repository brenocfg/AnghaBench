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
struct usb_serial_driver {int /*<<< orphan*/  dynids; } ;
struct device_driver {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct usb_serial_driver* to_usb_serial_driver (struct device_driver*) ; 
 int /*<<< orphan*/  usb_show_dynids (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ssize_t new_id_show(struct device_driver *driver, char *buf)
{
	struct usb_serial_driver *usb_drv = to_usb_serial_driver(driver);

	return usb_show_dynids(&usb_drv->dynids, buf);
}