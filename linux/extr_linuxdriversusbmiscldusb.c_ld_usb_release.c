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
struct ld_usb {int open_count; int /*<<< orphan*/  mutex; scalar_t__ interrupt_out_busy; int /*<<< orphan*/  write_wait; int /*<<< orphan*/ * intf; } ;
struct inode {int dummy; } ;
struct file {struct ld_usb* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 int HZ ; 
 int /*<<< orphan*/  ld_usb_abort_transfers (struct ld_usb*) ; 
 int /*<<< orphan*/  ld_usb_delete (struct ld_usb*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ld_usb_release(struct inode *inode, struct file *file)
{
	struct ld_usb *dev;
	int retval = 0;

	dev = file->private_data;

	if (dev == NULL) {
		retval = -ENODEV;
		goto exit;
	}

	if (mutex_lock_interruptible(&dev->mutex)) {
		retval = -ERESTARTSYS;
		goto exit;
	}

	if (dev->open_count != 1) {
		retval = -ENODEV;
		goto unlock_exit;
	}
	if (dev->intf == NULL) {
		/* the device was unplugged before the file was released */
		mutex_unlock(&dev->mutex);
		/* unlock here as ld_usb_delete frees dev */
		ld_usb_delete(dev);
		goto exit;
	}

	/* wait until write transfer is finished */
	if (dev->interrupt_out_busy)
		wait_event_interruptible_timeout(dev->write_wait, !dev->interrupt_out_busy, 2 * HZ);
	ld_usb_abort_transfers(dev);
	dev->open_count = 0;

unlock_exit:
	mutex_unlock(&dev->mutex);

exit:
	return retval;
}