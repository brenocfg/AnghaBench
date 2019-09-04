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
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRAMFS_BLOCKDEV ; 
 int /*<<< orphan*/  CONFIG_CRAMFS_MTD ; 
 int /*<<< orphan*/  ENOPROTOOPT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  cramfs_blkdev_fill_super ; 
 int /*<<< orphan*/  cramfs_mtd_fill_super ; 
 struct dentry* mount_bdev (struct file_system_type*,int,char const*,void*,int /*<<< orphan*/ ) ; 
 struct dentry* mount_mtd (struct file_system_type*,int,char const*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *cramfs_mount(struct file_system_type *fs_type, int flags,
				   const char *dev_name, void *data)
{
	struct dentry *ret = ERR_PTR(-ENOPROTOOPT);

	if (IS_ENABLED(CONFIG_CRAMFS_MTD)) {
		ret = mount_mtd(fs_type, flags, dev_name, data,
				cramfs_mtd_fill_super);
		if (!IS_ERR(ret))
			return ret;
	}
	if (IS_ENABLED(CONFIG_CRAMFS_BLOCKDEV)) {
		ret = mount_bdev(fs_type, flags, dev_name, data,
				 cramfs_blkdev_fill_super);
	}
	return ret;
}