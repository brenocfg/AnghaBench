#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; int /*<<< orphan*/  fl_type; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  lock_state; TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ OFFSET_MAX ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_inode (struct file*) ; 
 int posix_lock_file (struct file*,struct file_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_fsync (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_do_unlk(struct file *file, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	int ret;

	_enter("{%x:%u},%u", vnode->fid.vid, vnode->fid.vnode, fl->fl_type);

	/* Flush all pending writes before doing anything with locks. */
	vfs_fsync(file, 0);

	/* only whole-file unlocks are supported */
	if (fl->fl_start != 0 || fl->fl_end != OFFSET_MAX)
		return -EINVAL;

	ret = posix_lock_file(file, fl, NULL);
	_leave(" = %d [%u]", ret, vnode->lock_state);
	return ret;
}