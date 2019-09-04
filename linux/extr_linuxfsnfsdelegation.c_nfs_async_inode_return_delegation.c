#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct nfs_client {TYPE_1__* cl_mvops; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_4__ {int /*<<< orphan*/  delegation; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* match_stateid ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_2__* NFS_I (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs_delegation_run_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_mark_return_delegation (struct nfs_server*,struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int nfs_async_inode_return_delegation(struct inode *inode,
				      const nfs4_stateid *stateid)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs_client *clp = server->nfs_client;
	struct nfs_delegation *delegation;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation == NULL)
		goto out_enoent;
	if (stateid != NULL &&
	    !clp->cl_mvops->match_stateid(&delegation->stateid, stateid))
		goto out_enoent;
	nfs_mark_return_delegation(server, delegation);
	rcu_read_unlock();

	nfs_delegation_run_state_manager(clp);
	return 0;
out_enoent:
	rcu_read_unlock();
	return -ENOENT;
}