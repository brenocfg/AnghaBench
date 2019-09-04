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
struct sisusb_usb_data {int /*<<< orphan*/  kref; int /*<<< orphan*/  lock; scalar_t__ isopen; scalar_t__ present; } ;
struct inode {int dummy; } ;
struct file {struct sisusb_usb_data* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sisusb_delete ; 
 int /*<<< orphan*/  sisusb_kill_all_busy (struct sisusb_usb_data*) ; 
 int /*<<< orphan*/  sisusb_wait_all_out_complete (struct sisusb_usb_data*) ; 

__attribute__((used)) static int sisusb_release(struct inode *inode, struct file *file)
{
	struct sisusb_usb_data *sisusb;

	sisusb = file->private_data;
	if (!sisusb)
		return -ENODEV;

	mutex_lock(&sisusb->lock);

	if (sisusb->present) {
		/* Wait for all URBs to finish if device still present */
		if (!sisusb_wait_all_out_complete(sisusb))
			sisusb_kill_all_busy(sisusb);
	}

	sisusb->isopen = 0;
	file->private_data = NULL;

	mutex_unlock(&sisusb->lock);

	/* decrement the usage count on our device */
	kref_put(&sisusb->kref, sisusb_delete);

	return 0;
}