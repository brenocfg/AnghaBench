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
struct usb_serial_driver {int dummy; } ;
struct usb_serial {scalar_t__ minors_reserved; int /*<<< orphan*/  disc_mutex; int /*<<< orphan*/  kref; int /*<<< orphan*/  interface; struct usb_serial_driver* type; int /*<<< orphan*/  dev; } ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct usb_serial* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 

__attribute__((used)) static struct usb_serial *create_serial(struct usb_device *dev,
					struct usb_interface *interface,
					struct usb_serial_driver *driver)
{
	struct usb_serial *serial;

	serial = kzalloc(sizeof(*serial), GFP_KERNEL);
	if (!serial)
		return NULL;
	serial->dev = usb_get_dev(dev);
	serial->type = driver;
	serial->interface = usb_get_intf(interface);
	kref_init(&serial->kref);
	mutex_init(&serial->disc_mutex);
	serial->minors_reserved = 0;

	return serial;
}