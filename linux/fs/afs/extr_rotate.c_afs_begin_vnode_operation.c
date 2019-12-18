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
struct afs_vnode {scalar_t__ lock_state; int /*<<< orphan*/  io_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;
struct afs_fs_cursor {int /*<<< orphan*/  flags; int /*<<< orphan*/  error; TYPE_1__ ac; struct key* key; struct afs_vnode* vnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FS_CURSOR_CUR_ONLY ; 
 int /*<<< orphan*/  AFS_FS_CURSOR_INTR ; 
 int /*<<< orphan*/  AFS_FS_CURSOR_STOP ; 
 scalar_t__ AFS_VNODE_LOCK_NONE ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  memset (struct afs_fs_cursor*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 

bool afs_begin_vnode_operation(struct afs_fs_cursor *fc, struct afs_vnode *vnode,
			       struct key *key, bool intr)
{
	memset(fc, 0, sizeof(*fc));
	fc->vnode = vnode;
	fc->key = key;
	fc->ac.error = SHRT_MAX;
	fc->error = -EDESTADDRREQ;

	if (intr) {
		fc->flags |= AFS_FS_CURSOR_INTR;
		if (mutex_lock_interruptible(&vnode->io_lock) < 0) {
			fc->error = -EINTR;
			fc->flags |= AFS_FS_CURSOR_STOP;
			return false;
		}
	} else {
		mutex_lock(&vnode->io_lock);
	}

	if (vnode->lock_state != AFS_VNODE_LOCK_NONE)
		fc->flags |= AFS_FS_CURSOR_CUR_ONLY;
	return true;
}