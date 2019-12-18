#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct nfs_client {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_5__ {int /*<<< orphan*/  delegation; } ;
struct TYPE_4__ {struct nfs_client* nfs_client; } ;

/* Variables and functions */
 TYPE_3__* NFS_I (struct inode*) ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_schedule_state_manager (struct nfs_client*) ; 
 scalar_t__ nfs4_stateid_match_other (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_mark_test_expired_delegation (TYPE_1__*,struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nfs_inode_find_delegation_state_and_recover(struct inode *inode,
		const nfs4_stateid *stateid)
{
	struct nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	struct nfs_delegation *delegation;
	bool found = false;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation &&
	    nfs4_stateid_match_other(&delegation->stateid, stateid)) {
		nfs_mark_test_expired_delegation(NFS_SERVER(inode), delegation);
		found = true;
	}
	rcu_read_unlock();
	if (found)
		nfs4_schedule_state_manager(clp);
}