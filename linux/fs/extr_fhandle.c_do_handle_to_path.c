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
struct path {int /*<<< orphan*/  mnt; int /*<<< orphan*/  dentry; } ;
struct file_handle {int handle_bytes; int /*<<< orphan*/  handle_type; scalar_t__ f_handle; } ;
struct fid {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exportfs_decode_fh (int /*<<< orphan*/ ,struct fid*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_vfsmount_from_fd (int) ; 
 int /*<<< orphan*/  mntput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dentry_acceptable ; 

__attribute__((used)) static int do_handle_to_path(int mountdirfd, struct file_handle *handle,
			     struct path *path)
{
	int retval = 0;
	int handle_dwords;

	path->mnt = get_vfsmount_from_fd(mountdirfd);
	if (IS_ERR(path->mnt)) {
		retval = PTR_ERR(path->mnt);
		goto out_err;
	}
	/* change the handle size to multiple of sizeof(u32) */
	handle_dwords = handle->handle_bytes >> 2;
	path->dentry = exportfs_decode_fh(path->mnt,
					  (struct fid *)handle->f_handle,
					  handle_dwords, handle->handle_type,
					  vfs_dentry_acceptable, NULL);
	if (IS_ERR(path->dentry)) {
		retval = PTR_ERR(path->dentry);
		goto out_mnt;
	}
	return 0;
out_mnt:
	mntput(path->mnt);
out_err:
	return retval;
}