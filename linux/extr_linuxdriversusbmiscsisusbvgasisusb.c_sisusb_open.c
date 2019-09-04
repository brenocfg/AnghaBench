#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct sisusb_usb_data {int isopen; int /*<<< orphan*/  lock; int /*<<< orphan*/  kref; TYPE_1__* sisusb_dev; int /*<<< orphan*/  devinit; int /*<<< orphan*/  ready; int /*<<< orphan*/  present; } ;
struct inode {int dummy; } ;
struct file {struct sisusb_usb_data* private_data; } ;
struct TYPE_2__ {scalar_t__ speed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_driver ; 
 scalar_t__ sisusb_init_gfxdevice (struct sisusb_usb_data*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int) ; 
 struct sisusb_usb_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int sisusb_open(struct inode *inode, struct file *file)
{
	struct sisusb_usb_data *sisusb;
	struct usb_interface *interface;
	int subminor = iminor(inode);

	interface = usb_find_interface(&sisusb_driver, subminor);
	if (!interface)
		return -ENODEV;

	sisusb = usb_get_intfdata(interface);
	if (!sisusb)
		return -ENODEV;

	mutex_lock(&sisusb->lock);

	if (!sisusb->present || !sisusb->ready) {
		mutex_unlock(&sisusb->lock);
		return -ENODEV;
	}

	if (sisusb->isopen) {
		mutex_unlock(&sisusb->lock);
		return -EBUSY;
	}

	if (!sisusb->devinit) {
		if (sisusb->sisusb_dev->speed == USB_SPEED_HIGH ||
				sisusb->sisusb_dev->speed >= USB_SPEED_SUPER) {
			if (sisusb_init_gfxdevice(sisusb, 0)) {
				mutex_unlock(&sisusb->lock);
				dev_err(&sisusb->sisusb_dev->dev,
						"Failed to initialize device\n");
				return -EIO;
			}
		} else {
			mutex_unlock(&sisusb->lock);
			dev_err(&sisusb->sisusb_dev->dev,
					"Device not attached to USB 2.0 hub\n");
			return -EIO;
		}
	}

	/* Increment usage count for our sisusb */
	kref_get(&sisusb->kref);

	sisusb->isopen = 1;

	file->private_data = sisusb;

	mutex_unlock(&sisusb->lock);

	return 0;
}