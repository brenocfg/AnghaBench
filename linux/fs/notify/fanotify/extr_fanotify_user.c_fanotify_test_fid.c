#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_4__* dentry; } ;
struct TYPE_9__ {scalar_t__* val; } ;
typedef  TYPE_3__ __kernel_fsid_t ;
struct TYPE_10__ {TYPE_2__* d_sb; } ;
struct TYPE_8__ {TYPE_1__* s_export_op; TYPE_4__* s_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  fh_to_dentry; } ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int EXDEV ; 
 int vfs_get_fsid (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int fanotify_test_fid(struct path *path, __kernel_fsid_t *fsid)
{
	__kernel_fsid_t root_fsid;
	int err;

	/*
	 * Make sure path is not in filesystem with zero fsid (e.g. tmpfs).
	 */
	err = vfs_get_fsid(path->dentry, fsid);
	if (err)
		return err;

	if (!fsid->val[0] && !fsid->val[1])
		return -ENODEV;

	/*
	 * Make sure path is not inside a filesystem subvolume (e.g. btrfs)
	 * which uses a different fsid than sb root.
	 */
	err = vfs_get_fsid(path->dentry->d_sb->s_root, &root_fsid);
	if (err)
		return err;

	if (root_fsid.val[0] != fsid->val[0] ||
	    root_fsid.val[1] != fsid->val[1])
		return -EXDEV;

	/*
	 * We need to make sure that the file system supports at least
	 * encoding a file handle so user can use name_to_handle_at() to
	 * compare fid returned with event to the file handle of watched
	 * objects. However, name_to_handle_at() requires that the
	 * filesystem also supports decoding file handles.
	 */
	if (!path->dentry->d_sb->s_export_op ||
	    !path->dentry->d_sb->s_export_op->fh_to_dentry)
		return -EOPNOTSUPP;

	return 0;
}