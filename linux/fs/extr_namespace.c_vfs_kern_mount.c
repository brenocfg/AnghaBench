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
struct vfsmount {int dummy; } ;
struct fs_context {int dummy; } ;
struct file_system_type {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vfsmount* ERR_CAST (struct fs_context*) ; 
 struct vfsmount* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct fs_context*) ; 
 struct vfsmount* fc_mount (struct fs_context*) ; 
 struct fs_context* fs_context_for_mount (struct file_system_type*,int) ; 
 int parse_monolithic_mount_data (struct fs_context*,void*) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int vfs_parse_fs_string (struct fs_context*,char*,char const*,int /*<<< orphan*/ ) ; 

struct vfsmount *vfs_kern_mount(struct file_system_type *type,
				int flags, const char *name,
				void *data)
{
	struct fs_context *fc;
	struct vfsmount *mnt;
	int ret = 0;

	if (!type)
		return ERR_PTR(-EINVAL);

	fc = fs_context_for_mount(type, flags);
	if (IS_ERR(fc))
		return ERR_CAST(fc);

	if (name)
		ret = vfs_parse_fs_string(fc, "source",
					  name, strlen(name));
	if (!ret)
		ret = parse_monolithic_mount_data(fc, data);
	if (!ret)
		mnt = fc_mount(fc);
	else
		mnt = ERR_PTR(ret);

	put_fs_context(fc);
	return mnt;
}