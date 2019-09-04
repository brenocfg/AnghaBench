#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;
struct usbport_trig_port {struct usbport_trig_port* port_name; TYPE_2__ attr; int /*<<< orphan*/  list; } ;
struct usbport_trig_data {struct led_classdev* led_cdev; } ;
struct led_classdev {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usbport_trig_port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_3__ ports_group ; 
 int /*<<< orphan*/  sysfs_remove_file_from_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbport_trig_remove_port(struct usbport_trig_data *usbport_data,
				     struct usbport_trig_port *port)
{
	struct led_classdev *led_cdev = usbport_data->led_cdev;

	list_del(&port->list);
	sysfs_remove_file_from_group(&led_cdev->dev->kobj, &port->attr.attr,
				     ports_group.name);
	kfree(port->port_name);
	kfree(port);
}