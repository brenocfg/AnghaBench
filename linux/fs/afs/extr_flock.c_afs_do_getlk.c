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
struct key {int dummy; } ;
struct file_lock {int /*<<< orphan*/  fl_type; scalar_t__ fl_pid; int /*<<< orphan*/  fl_end; scalar_t__ fl_start; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock_count; } ;
struct afs_vnode {scalar_t__ lock_state; TYPE_1__ status; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ AFS_VNODE_LOCK_DELETED ; 
 int ENOENT ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int,int /*<<< orphan*/ ) ; 
 int afs_fetch_status (struct afs_vnode*,struct key*,int,int /*<<< orphan*/ *) ; 
 struct key* afs_file_key (struct file*) ; 
 int /*<<< orphan*/  locks_inode (struct file*) ; 
 int /*<<< orphan*/  posix_test_lock (struct file*,struct file_lock*) ; 

__attribute__((used)) static int afs_do_getlk(struct file *file, struct file_lock *fl)
{
	struct afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	struct key *key = afs_file_key(file);
	int ret, lock_count;

	_enter("");

	if (vnode->lock_state == AFS_VNODE_LOCK_DELETED)
		return -ENOENT;

	fl->fl_type = F_UNLCK;

	/* check local lock records first */
	posix_test_lock(file, fl);
	if (fl->fl_type == F_UNLCK) {
		/* no local locks; consult the server */
		ret = afs_fetch_status(vnode, key, false, NULL);
		if (ret < 0)
			goto error;

		lock_count = READ_ONCE(vnode->status.lock_count);
		if (lock_count != 0) {
			if (lock_count > 0)
				fl->fl_type = F_RDLCK;
			else
				fl->fl_type = F_WRLCK;
			fl->fl_start = 0;
			fl->fl_end = OFFSET_MAX;
			fl->fl_pid = 0;
		}
	}

	ret = 0;
error:
	_leave(" = %d [%hd]", ret, fl->fl_type);
	return ret;
}