#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int mode; struct usbport_trig_port* name; } ;
struct TYPE_7__ {TYPE_3__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct usbport_trig_port {int portnum; struct usbport_trig_port* port_name; int /*<<< orphan*/  list; TYPE_2__ attr; int /*<<< orphan*/  observed; struct usb_device* hub; struct usbport_trig_data* data; } ;
struct usbport_trig_data {int /*<<< orphan*/  ports; struct led_classdev* led_cdev; } ;
struct usb_device {int dummy; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  kfree (struct usbport_trig_port*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ ports_group ; 
 int /*<<< orphan*/  snprintf (struct usbport_trig_port*,size_t,char*,char const*,int) ; 
 int strlen (char const*) ; 
 int sysfs_add_file_to_group (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_3__*) ; 
 int /*<<< orphan*/  usbport_trig_port_observed (struct usbport_trig_data*,struct usb_device*,int) ; 
 int /*<<< orphan*/  usbport_trig_port_show ; 
 int /*<<< orphan*/  usbport_trig_port_store ; 

__attribute__((used)) static int usbport_trig_add_port(struct usbport_trig_data *usbport_data,
				 struct usb_device *usb_dev,
				 const char *hub_name, int portnum)
{
	struct led_classdev *led_cdev = usbport_data->led_cdev;
	struct usbport_trig_port *port;
	size_t len;
	int err;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port) {
		err = -ENOMEM;
		goto err_out;
	}

	port->data = usbport_data;
	port->hub = usb_dev;
	port->portnum = portnum;
	port->observed = usbport_trig_port_observed(usbport_data, usb_dev,
						    portnum);

	len = strlen(hub_name) + 8;
	port->port_name = kzalloc(len, GFP_KERNEL);
	if (!port->port_name) {
		err = -ENOMEM;
		goto err_free_port;
	}
	snprintf(port->port_name, len, "%s-port%d", hub_name, portnum);

	sysfs_attr_init(&port->attr.attr);
	port->attr.attr.name = port->port_name;
	port->attr.attr.mode = S_IRUSR | S_IWUSR;
	port->attr.show = usbport_trig_port_show;
	port->attr.store = usbport_trig_port_store;

	err = sysfs_add_file_to_group(&led_cdev->dev->kobj, &port->attr.attr,
				      ports_group.name);
	if (err)
		goto err_free_port_name;

	list_add_tail(&port->list, &usbport_data->ports);

	return 0;

err_free_port_name:
	kfree(port->port_name);
err_free_port:
	kfree(port);
err_out:
	return err;
}