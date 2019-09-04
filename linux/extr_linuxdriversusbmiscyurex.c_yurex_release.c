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
struct usb_yurex {int /*<<< orphan*/  kref; } ;
struct inode {int dummy; } ;
struct file {struct usb_yurex* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yurex_delete ; 

__attribute__((used)) static int yurex_release(struct inode *inode, struct file *file)
{
	struct usb_yurex *dev;

	dev = file->private_data;
	if (dev == NULL)
		return -ENODEV;

	/* decrement the count on our device */
	kref_put(&dev->kref, yurex_delete);
	return 0;
}