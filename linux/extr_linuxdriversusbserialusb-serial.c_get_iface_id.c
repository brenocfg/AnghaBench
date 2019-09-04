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
struct usb_serial_driver {int /*<<< orphan*/  id_table; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct usb_device_id* match_dynamic_id (struct usb_interface*,struct usb_serial_driver*) ; 
 struct usb_device_id* usb_match_id (struct usb_interface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct usb_device_id *get_iface_id(struct usb_serial_driver *drv,
						struct usb_interface *intf)
{
	const struct usb_device_id *id;

	id = usb_match_id(intf, drv->id_table);
	if (id) {
		dev_dbg(&intf->dev, "static descriptor matches\n");
		goto exit;
	}
	id = match_dynamic_id(intf, drv);
	if (id)
		dev_dbg(&intf->dev, "dynamic descriptor matches\n");
exit:
	return id;
}