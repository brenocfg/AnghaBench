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
 int /*<<< orphan*/  CONFIG_TMPFS ; 
 int /*<<< orphan*/  ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tmpfs ; 
 struct dentry* mount_nodev (struct file_system_type*,int,void*,void*) ; 
 void* ramfs_fill_super ; 
 void* shmem_fill_super ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static struct dentry *rootfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	static unsigned long once;
	void *fill = ramfs_fill_super;

	if (test_and_set_bit(0, &once))
		return ERR_PTR(-ENODEV);

	if (IS_ENABLED(CONFIG_TMPFS) && is_tmpfs)
		fill = shmem_fill_super;

	return mount_nodev(fs_type, flags, data, fill);
}