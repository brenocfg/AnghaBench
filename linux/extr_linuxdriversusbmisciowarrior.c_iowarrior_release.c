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
struct iowarrior {scalar_t__ opened; int /*<<< orphan*/  mutex; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  int_in_urb; scalar_t__ present; int /*<<< orphan*/  minor; TYPE_1__* interface; } ;
struct inode {int dummy; } ;
struct file {struct iowarrior* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowarrior_delete (struct iowarrior*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iowarrior_release(struct inode *inode, struct file *file)
{
	struct iowarrior *dev;
	int retval = 0;

	dev = file->private_data;
	if (!dev)
		return -ENODEV;

	dev_dbg(&dev->interface->dev, "minor %d\n", dev->minor);

	/* lock our device */
	mutex_lock(&dev->mutex);

	if (dev->opened <= 0) {
		retval = -ENODEV;	/* close called more than once */
		mutex_unlock(&dev->mutex);
	} else {
		dev->opened = 0;	/* we're closing now */
		retval = 0;
		if (dev->present) {
			/*
			   The device is still connected so we only shutdown
			   pending read-/write-ops.
			 */
			usb_kill_urb(dev->int_in_urb);
			wake_up_interruptible(&dev->read_wait);
			wake_up_interruptible(&dev->write_wait);
			mutex_unlock(&dev->mutex);
		} else {
			/* The device was unplugged, cleanup resources */
			mutex_unlock(&dev->mutex);
			iowarrior_delete(dev);
		}
	}
	return retval;
}