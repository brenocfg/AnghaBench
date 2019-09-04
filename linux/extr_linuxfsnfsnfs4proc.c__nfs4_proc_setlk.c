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
struct nfs_inode {int /*<<< orphan*/  rwsem; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_delegreturn_mutex; } ;
struct nfs4_state {int /*<<< orphan*/  inode; int /*<<< orphan*/  flags; struct nfs4_state_owner* owner; } ;
struct file_lock {unsigned char fl_flags; } ;

/* Variables and functions */
 unsigned char FL_ACCESS ; 
 unsigned char FL_SLEEP ; 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_LOCK_NEW ; 
 int _nfs4_do_setlk (struct nfs4_state*,int,struct file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int locks_lock_inode_wait (int /*<<< orphan*/ ,struct file_lock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nfs4_proc_setlk(struct nfs4_state *state, int cmd, struct file_lock *request)
{
	struct nfs_inode *nfsi = NFS_I(state->inode);
	struct nfs4_state_owner *sp = state->owner;
	unsigned char fl_flags = request->fl_flags;
	int status;

	request->fl_flags |= FL_ACCESS;
	status = locks_lock_inode_wait(state->inode, request);
	if (status < 0)
		goto out;
	mutex_lock(&sp->so_delegreturn_mutex);
	down_read(&nfsi->rwsem);
	if (test_bit(NFS_DELEGATED_STATE, &state->flags)) {
		/* Yes: cache locks! */
		/* ...but avoid races with delegation recall... */
		request->fl_flags = fl_flags & ~FL_SLEEP;
		status = locks_lock_inode_wait(state->inode, request);
		up_read(&nfsi->rwsem);
		mutex_unlock(&sp->so_delegreturn_mutex);
		goto out;
	}
	up_read(&nfsi->rwsem);
	mutex_unlock(&sp->so_delegreturn_mutex);
	status = _nfs4_do_setlk(state, cmd, request, NFS_LOCK_NEW);
out:
	request->fl_flags = fl_flags;
	return status;
}