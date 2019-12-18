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
struct nfs_inode {int /*<<< orphan*/  delegation; } ;
struct nfs_delegation {int /*<<< orphan*/  cred; int /*<<< orphan*/  stateid; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 struct cred* get_cred (int /*<<< orphan*/ ) ; 
 int nfs4_is_valid_delegation (struct nfs_delegation*,int) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mark_delegation_referenced (struct nfs_delegation*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool nfs4_copy_delegation_stateid(struct inode *inode, fmode_t flags,
		nfs4_stateid *dst, const struct cred **cred)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_delegation *delegation;
	bool ret;

	flags &= FMODE_READ|FMODE_WRITE;
	rcu_read_lock();
	delegation = rcu_dereference(nfsi->delegation);
	ret = nfs4_is_valid_delegation(delegation, flags);
	if (ret) {
		nfs4_stateid_copy(dst, &delegation->stateid);
		nfs_mark_delegation_referenced(delegation);
		if (cred)
			*cred = get_cred(delegation->cred);
	}
	rcu_read_unlock();
	return ret;
}