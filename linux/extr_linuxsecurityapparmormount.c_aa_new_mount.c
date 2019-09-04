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
struct file_system_type {int fs_flags; } ;
struct aa_profile {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int ENODEV ; 
 int ENOENT ; 
 int FS_BINARY_MOUNTDATA ; 
 int FS_REQUIRES_DEV ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int fn_for_each_confined (struct aa_label*,struct aa_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_buffers (char*,char*) ; 
 struct file_system_type* get_fs_type (char const*) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  match_mnt (struct aa_profile*,struct path const*,char*,struct path*,char*,char const*,unsigned long,void*,int) ; 
 int /*<<< orphan*/  match_mnt_path_str (struct aa_profile*,struct path const*,char*,char const*,char const*,unsigned long,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_buffers (char*,char*) ; 
 int /*<<< orphan*/  put_filesystem (struct file_system_type*) ; 

int aa_new_mount(struct aa_label *label, const char *dev_name,
		 const struct path *path, const char *type, unsigned long flags,
		 void *data)
{
	struct aa_profile *profile;
	char *buffer = NULL, *dev_buffer = NULL;
	bool binary = true;
	int error;
	int requires_dev = 0;
	struct path tmp_path, *dev_path = NULL;

	AA_BUG(!label);
	AA_BUG(!path);

	if (type) {
		struct file_system_type *fstype;

		fstype = get_fs_type(type);
		if (!fstype)
			return -ENODEV;
		binary = fstype->fs_flags & FS_BINARY_MOUNTDATA;
		requires_dev = fstype->fs_flags & FS_REQUIRES_DEV;
		put_filesystem(fstype);

		if (requires_dev) {
			if (!dev_name || !*dev_name)
				return -ENOENT;

			error = kern_path(dev_name, LOOKUP_FOLLOW, &tmp_path);
			if (error)
				return error;
			dev_path = &tmp_path;
		}
	}

	get_buffers(buffer, dev_buffer);
	if (dev_path) {
		error = fn_for_each_confined(label, profile,
			match_mnt(profile, path, buffer, dev_path, dev_buffer,
				  type, flags, data, binary));
	} else {
		error = fn_for_each_confined(label, profile,
			match_mnt_path_str(profile, path, buffer, dev_name,
					   type, flags, data, binary, NULL));
	}
	put_buffers(buffer, dev_buffer);
	if (dev_path)
		path_put(dev_path);

	return error;
}