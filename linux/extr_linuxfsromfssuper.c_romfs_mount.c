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
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *romfs_mount(struct file_system_type *fs_type,
			int flags, const char *dev_name,
			void *data)
{
	struct dentry *ret = ERR_PTR(-EINVAL);

#ifdef CONFIG_ROMFS_ON_MTD
	ret = mount_mtd(fs_type, flags, dev_name, data, romfs_fill_super);
#endif
#ifdef CONFIG_ROMFS_ON_BLOCK
	if (ret == ERR_PTR(-EINVAL))
		ret = mount_bdev(fs_type, flags, dev_name, data,
				  romfs_fill_super);
#endif
	return ret;
}