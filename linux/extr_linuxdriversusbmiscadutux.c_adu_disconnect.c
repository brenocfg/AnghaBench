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
struct adu_device {int /*<<< orphan*/  open_count; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  adu_class ; 
 int /*<<< orphan*/  adu_delete (struct adu_device*) ; 
 int /*<<< orphan*/  adutux_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct adu_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adu_disconnect(struct usb_interface *interface)
{
	struct adu_device *dev;

	dev = usb_get_intfdata(interface);

	mutex_lock(&dev->mtx);	/* not interruptible */
	dev->udev = NULL;	/* poison */
	usb_deregister_dev(interface, &adu_class);
	mutex_unlock(&dev->mtx);

	mutex_lock(&adutux_mutex);
	usb_set_intfdata(interface, NULL);

	/* if the device is not opened, then we clean up right now */
	if (!dev->open_count)
		adu_delete(dev);

	mutex_unlock(&adutux_mutex);
}