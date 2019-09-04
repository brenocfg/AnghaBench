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
struct inode {int dummy; } ;
struct file {struct fb_info* private_data; } ;
struct fb_info {int /*<<< orphan*/  deferred_work; int /*<<< orphan*/  fbdefio; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct inode* file_inode (struct file*) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int fb_deferred_io_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct fb_info *info = file->private_data;
	struct inode *inode = file_inode(file);
	int err = file_write_and_wait_range(file, start, end);
	if (err)
		return err;

	/* Skip if deferred io is compiled-in but disabled on this fbdev */
	if (!info->fbdefio)
		return 0;

	inode_lock(inode);
	/* Kill off the delayed work */
	cancel_delayed_work_sync(&info->deferred_work);

	/* Run it immediately */
	schedule_delayed_work(&info->deferred_work, 0);
	inode_unlock(inode);

	return 0;
}