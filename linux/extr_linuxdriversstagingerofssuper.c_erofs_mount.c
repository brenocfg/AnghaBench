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
struct erofs_mount_private {char const* dev_name; void* options; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  erofs_fill_super ; 
 struct dentry* mount_bdev (struct file_system_type*,int,char const*,struct erofs_mount_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *erofs_mount(
	struct file_system_type *fs_type, int flags,
	const char *dev_name, void *data)
{
	struct erofs_mount_private priv = {
		.dev_name = dev_name,
		.options = data
	};

	return mount_bdev(fs_type, flags, dev_name,
		&priv, erofs_fill_super);
}