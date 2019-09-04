#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nfs_delegation {int flags; } ;
struct nfs_client {int /*<<< orphan*/  cl_hostname; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  delegation; scalar_t__ do_recall; int /*<<< orphan*/  pagemod_limit; int /*<<< orphan*/  delegation_type; } ;
struct TYPE_6__ {int claim; } ;
struct nfs4_opendata {TYPE_3__ o_res; TYPE_2__* owner; TYPE_1__ o_arg; } ;
struct TYPE_10__ {int /*<<< orphan*/  delegation; } ;
struct TYPE_9__ {struct nfs_client* nfs_client; } ;
struct TYPE_7__ {int /*<<< orphan*/  so_cred; } ;

/* Variables and functions */
#define  NFS4_OPEN_CLAIM_DELEGATE_CUR 129 
#define  NFS4_OPEN_CLAIM_DELEG_CUR_FH 128 
 int NFS_DELEGATION_NEED_RECLAIM ; 
 TYPE_5__* NFS_I (int /*<<< orphan*/ ) ; 
 TYPE_4__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_async_inode_return_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_inode_reclaim_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inode_set_delegation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void
nfs4_opendata_check_deleg(struct nfs4_opendata *data, struct nfs4_state *state)
{
	struct nfs_client *clp = NFS_SERVER(state->inode)->nfs_client;
	struct nfs_delegation *delegation;
	int delegation_flags = 0;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(state->inode)->delegation);
	if (delegation)
		delegation_flags = delegation->flags;
	rcu_read_unlock();
	switch (data->o_arg.claim) {
	default:
		break;
	case NFS4_OPEN_CLAIM_DELEGATE_CUR:
	case NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		pr_err_ratelimited("NFS: Broken NFSv4 server %s is "
				   "returning a delegation for "
				   "OPEN(CLAIM_DELEGATE_CUR)\n",
				   clp->cl_hostname);
		return;
	}
	if ((delegation_flags & 1UL<<NFS_DELEGATION_NEED_RECLAIM) == 0)
		nfs_inode_set_delegation(state->inode,
				data->owner->so_cred,
				data->o_res.delegation_type,
				&data->o_res.delegation,
				data->o_res.pagemod_limit);
	else
		nfs_inode_reclaim_delegation(state->inode,
				data->owner->so_cred,
				data->o_res.delegation_type,
				&data->o_res.delegation,
				data->o_res.pagemod_limit);

	if (data->o_res.do_recall)
		nfs_async_inode_return_delegation(state->inode,
						  &data->o_res.delegation);
}