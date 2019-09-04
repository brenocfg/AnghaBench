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
typedef  int umode_t ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUGO ; 
 struct dentry* debugfs_create_file_unsafe (char const*,int,struct dentry*,void*,struct file_operations const*) ; 

__attribute__((used)) static struct dentry *debugfs_create_mode_unsafe(const char *name, umode_t mode,
					struct dentry *parent, void *value,
					const struct file_operations *fops,
					const struct file_operations *fops_ro,
					const struct file_operations *fops_wo)
{
	/* if there are no write bits set, make read only */
	if (!(mode & S_IWUGO))
		return debugfs_create_file_unsafe(name, mode, parent, value,
						fops_ro);
	/* if there are no read bits set, make write only */
	if (!(mode & S_IRUGO))
		return debugfs_create_file_unsafe(name, mode, parent, value,
						fops_wo);

	return debugfs_create_file_unsafe(name, mode, parent, value, fops);
}