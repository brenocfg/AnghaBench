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
struct printer_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  printer_status; scalar_t__ printer_cdev_open; } ;
struct inode {int dummy; } ;
struct file {struct printer_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct printer_dev*,char*) ; 
 int /*<<< orphan*/  PRINTER_SELECTED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
printer_close(struct inode *inode, struct file *fd)
{
	struct printer_dev	*dev = fd->private_data;
	unsigned long		flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->printer_cdev_open = 0;
	fd->private_data = NULL;
	/* Change printer status to show that the printer is off-line. */
	dev->printer_status &= ~PRINTER_SELECTED;
	spin_unlock_irqrestore(&dev->lock, flags);

	DBG(dev, "printer_close\n");

	return 0;
}