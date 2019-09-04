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
struct hso_device {int port_spec; int /*<<< orphan*/  async_put_intf; int /*<<< orphan*/  async_get_intf; int /*<<< orphan*/  mutex; int /*<<< orphan*/  ref; struct usb_interface* interface; int /*<<< orphan*/  usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_get_intf ; 
 int /*<<< orphan*/  async_put_intf ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct hso_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hso_device *hso_create_device(struct usb_interface *intf,
					    int port_spec)
{
	struct hso_device *hso_dev;

	hso_dev = kzalloc(sizeof(*hso_dev), GFP_ATOMIC);
	if (!hso_dev)
		return NULL;

	hso_dev->port_spec = port_spec;
	hso_dev->usb = interface_to_usbdev(intf);
	hso_dev->interface = intf;
	kref_init(&hso_dev->ref);
	mutex_init(&hso_dev->mutex);

	INIT_WORK(&hso_dev->async_get_intf, async_get_intf);
	INIT_WORK(&hso_dev->async_put_intf, async_put_intf);

	return hso_dev;
}