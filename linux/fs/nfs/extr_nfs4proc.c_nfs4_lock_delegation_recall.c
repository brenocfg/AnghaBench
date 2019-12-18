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
struct nfs_server {int dummy; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct file_lock {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  NFS_LOCK_NEW ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int _nfs4_do_setlk (struct nfs4_state*,int /*<<< orphan*/ ,struct file_lock*,int /*<<< orphan*/ ) ; 
 int nfs4_handle_delegation_recall_error (struct nfs_server*,struct nfs4_state*,int /*<<< orphan*/  const*,struct file_lock*,int) ; 
 int nfs4_set_lock_state (struct nfs4_state*,struct file_lock*) ; 

int nfs4_lock_delegation_recall(struct file_lock *fl, struct nfs4_state *state, const nfs4_stateid *stateid)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	int err;

	err = nfs4_set_lock_state(state, fl);
	if (err != 0)
		return err;
	err = _nfs4_do_setlk(state, F_SETLK, fl, NFS_LOCK_NEW);
	return nfs4_handle_delegation_recall_error(server, state, stateid, fl, err);
}