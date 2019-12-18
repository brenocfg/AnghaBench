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
struct path {int dummy; } ;
struct fs_context {int dummy; } ;
struct file_system_type {int fs_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int FS_HAS_SUBTYPE ; 
 scalar_t__ IS_ERR (struct fs_context*) ; 
 int PTR_ERR (struct fs_context*) ; 
 int do_new_mount_fc (struct fs_context*,struct path*,int) ; 
 struct fs_context* fs_context_for_mount (struct file_system_type*,int) ; 
 struct file_system_type* get_fs_type (char const*) ; 
 int /*<<< orphan*/  mount_capable (struct fs_context*) ; 
 int parse_monolithic_mount_data (struct fs_context*,void*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int vfs_get_tree (struct fs_context*) ; 
 int vfs_parse_fs_string (struct fs_context*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_new_mount(struct path *path, const char *fstype, int sb_flags,
			int mnt_flags, const char *name, void *data)
{
	struct file_system_type *type;
	struct fs_context *fc;
	const char *subtype = NULL;
	int err = 0;

	if (!fstype)
		return -EINVAL;

	type = get_fs_type(fstype);
	if (!type)
		return -ENODEV;

	if (type->fs_flags & FS_HAS_SUBTYPE) {
		subtype = strchr(fstype, '.');
		if (subtype) {
			subtype++;
			if (!*subtype) {
				put_filesystem(type);
				return -EINVAL;
			}
		}
	}

	fc = fs_context_for_mount(type, sb_flags);
	put_filesystem(type);
	if (IS_ERR(fc))
		return PTR_ERR(fc);

	if (subtype)
		err = vfs_parse_fs_string(fc, "subtype",
					  subtype, strlen(subtype));
	if (!err && name)
		err = vfs_parse_fs_string(fc, "source", name, strlen(name));
	if (!err)
		err = parse_monolithic_mount_data(fc, data);
	if (!err && !mount_capable(fc))
		err = -EPERM;
	if (!err)
		err = vfs_get_tree(fc);
	if (!err)
		err = do_new_mount_fc(fc, path, mnt_flags);

	put_fs_context(fc);
	return err;
}