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
struct super_block {int dummy; } ;
struct object_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int
adfs_dir_update(struct super_block *sb, struct object_info *obj, int wait)
{
	int ret = -EINVAL;
#ifdef CONFIG_ADFS_FS_RW
	const struct adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	struct adfs_dir dir;

	printk(KERN_INFO "adfs_dir_update: object %06X in dir %06X\n",
		 obj->file_id, obj->parent_id);

	if (!ops->update) {
		ret = -EINVAL;
		goto out;
	}

	ret = ops->read(sb, obj->parent_id, 0, &dir);
	if (ret)
		goto out;

	write_lock(&adfs_dir_lock);
	ret = ops->update(&dir, obj);
	write_unlock(&adfs_dir_lock);

	if (wait) {
		int err = ops->sync(&dir);
		if (!ret)
			ret = err;
	}

	ops->free(&dir);
out:
#endif
	return ret;
}