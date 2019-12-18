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
struct inode {int dummy; } ;
struct hfs_readdir_data {int /*<<< orphan*/  list; } ;
struct file {struct hfs_readdir_data* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_dir_lock; } ;

/* Variables and functions */
 TYPE_1__* HFS_I (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hfs_readdir_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfs_dir_release(struct inode *inode, struct file *file)
{
	struct hfs_readdir_data *rd = file->private_data;
	if (rd) {
		spin_lock(&HFS_I(inode)->open_dir_lock);
		list_del(&rd->list);
		spin_unlock(&HFS_I(inode)->open_dir_lock);
		kfree(rd);
	}
	return 0;
}