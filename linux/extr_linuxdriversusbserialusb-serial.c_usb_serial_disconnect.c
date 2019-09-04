#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  work; TYPE_2__ port; } ;
struct usb_serial {int disconnected; int num_ports; TYPE_1__* type; struct usb_serial_port** port; int /*<<< orphan*/  disc_mutex; } ;
struct device {int dummy; } ;
struct usb_interface {struct device dev; } ;
struct tty_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disconnect ) (struct usb_serial*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct usb_serial*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 
 struct usb_serial* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_serial_console_disconnect (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_serial_port_poison_urbs (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_put (struct usb_serial*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_serial_disconnect(struct usb_interface *interface)
{
	int i;
	struct usb_serial *serial = usb_get_intfdata(interface);
	struct device *dev = &interface->dev;
	struct usb_serial_port *port;
	struct tty_struct *tty;

	usb_serial_console_disconnect(serial);

	mutex_lock(&serial->disc_mutex);
	/* must set a flag, to signal subdrivers */
	serial->disconnected = 1;
	mutex_unlock(&serial->disc_mutex);

	for (i = 0; i < serial->num_ports; ++i) {
		port = serial->port[i];
		tty = tty_port_tty_get(&port->port);
		if (tty) {
			tty_vhangup(tty);
			tty_kref_put(tty);
		}
		usb_serial_port_poison_urbs(port);
		wake_up_interruptible(&port->port.delta_msr_wait);
		cancel_work_sync(&port->work);
		if (device_is_registered(&port->dev))
			device_del(&port->dev);
	}
	if (serial->type->disconnect)
		serial->type->disconnect(serial);

	/* let the last holder of this object cause it to be cleaned up */
	usb_serial_put(serial);
	dev_info(dev, "device disconnected\n");
}