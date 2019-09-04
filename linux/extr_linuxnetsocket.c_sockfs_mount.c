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
 int /*<<< orphan*/  SOCKFS_MAGIC ; 
 struct dentry* mount_pseudo_xattr (struct file_system_type*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfs_dentry_operations ; 
 int /*<<< orphan*/  sockfs_ops ; 
 int /*<<< orphan*/  sockfs_xattr_handlers ; 

__attribute__((used)) static struct dentry *sockfs_mount(struct file_system_type *fs_type,
			 int flags, const char *dev_name, void *data)
{
	return mount_pseudo_xattr(fs_type, "socket:", &sockfs_ops,
				  sockfs_xattr_handlers,
				  &sockfs_dentry_operations, SOCKFS_MAGIC);
}