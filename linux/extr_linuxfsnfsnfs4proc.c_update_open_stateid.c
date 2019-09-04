#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_inode {int /*<<< orphan*/  delegation; } ;
struct TYPE_12__ {scalar_t__ type; } ;
struct nfs_delegation {int type; int /*<<< orphan*/  lock; TYPE_2__ stateid; int /*<<< orphan*/  flags; } ;
struct nfs_client {int dummy; } ;
struct nfs4_state {TYPE_1__* owner; int /*<<< orphan*/  flags; int /*<<< orphan*/  inode; } ;
typedef  TYPE_2__ nfs4_stateid ;
typedef  int fmode_t ;
struct TYPE_11__ {int /*<<< orphan*/  so_cred; int /*<<< orphan*/  so_lock; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFS_DELEGATION_RETURNING ; 
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_STATE_RECLAIM_NOGRACE ; 
 int /*<<< orphan*/  nfs4_schedule_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_stateid_match (TYPE_2__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  nfs4_test_and_free_stateid (struct nfs_server*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_mark_delegation_referenced (struct nfs_delegation*) ; 
 int /*<<< orphan*/  nfs_state_set_delegation (struct nfs4_state*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  nfs_state_set_open_stateid (struct nfs4_state*,TYPE_2__ const*,int,TYPE_2__*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_open_stateflags (struct nfs4_state*,int) ; 

__attribute__((used)) static int update_open_stateid(struct nfs4_state *state,
		const nfs4_stateid *open_stateid,
		const nfs4_stateid *delegation,
		fmode_t fmode)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs_client *clp = server->nfs_client;
	struct nfs_inode *nfsi = NFS_I(state->inode);
	struct nfs_delegation *deleg_cur;
	nfs4_stateid freeme = { };
	int ret = 0;

	fmode &= (FMODE_READ|FMODE_WRITE);

	rcu_read_lock();
	spin_lock(&state->owner->so_lock);
	if (open_stateid != NULL) {
		nfs_state_set_open_stateid(state, open_stateid, fmode, &freeme);
		ret = 1;
	}

	deleg_cur = rcu_dereference(nfsi->delegation);
	if (deleg_cur == NULL)
		goto no_delegation;

	spin_lock(&deleg_cur->lock);
	if (rcu_dereference(nfsi->delegation) != deleg_cur ||
	   test_bit(NFS_DELEGATION_RETURNING, &deleg_cur->flags) ||
	    (deleg_cur->type & fmode) != fmode)
		goto no_delegation_unlock;

	if (delegation == NULL)
		delegation = &deleg_cur->stateid;
	else if (!nfs4_stateid_match(&deleg_cur->stateid, delegation))
		goto no_delegation_unlock;

	nfs_mark_delegation_referenced(deleg_cur);
	nfs_state_set_delegation(state, &deleg_cur->stateid, fmode);
	ret = 1;
no_delegation_unlock:
	spin_unlock(&deleg_cur->lock);
no_delegation:
	if (ret)
		update_open_stateflags(state, fmode);
	spin_unlock(&state->owner->so_lock);
	rcu_read_unlock();

	if (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags))
		nfs4_schedule_state_manager(clp);
	if (freeme.type != 0)
		nfs4_test_and_free_stateid(server, &freeme,
				state->owner->so_cred);

	return ret;
}