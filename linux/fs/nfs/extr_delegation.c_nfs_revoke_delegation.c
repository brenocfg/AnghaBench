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
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_2__ {int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_inode_find_state_and_recover (struct inode*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_mark_delegation_revoked (int /*<<< orphan*/ ,struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool nfs_revoke_delegation(struct inode *inode,
		const nfs4_stateid *stateid)
{
	struct nfs_delegation *delegation;
	nfs4_stateid tmp;
	bool ret = false;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation == NULL)
		goto out;
	if (stateid == NULL) {
		nfs4_stateid_copy(&tmp, &delegation->stateid);
		stateid = &tmp;
	} else if (!nfs4_stateid_match(stateid, &delegation->stateid))
		goto out;
	nfs_mark_delegation_revoked(NFS_SERVER(inode), delegation);
	ret = true;
out:
	rcu_read_unlock();
	if (ret)
		nfs_inode_find_state_and_recover(inode, stateid);
	return ret;
}