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
struct nfs_delegation {unsigned long pagemod_limit; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; struct cred* cred; int /*<<< orphan*/  type; int /*<<< orphan*/  stateid; int /*<<< orphan*/ * inode; } ;
struct inode {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {int /*<<< orphan*/  delegation; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATION_NEED_RECLAIM ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cred* get_cred (struct cred const*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nfs_inode_set_delegation (struct inode*,struct cred const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned long) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfs4_reclaim_delegation (struct inode*,int /*<<< orphan*/ ) ; 

void nfs_inode_reclaim_delegation(struct inode *inode, const struct cred *cred,
				  fmode_t type,
				  const nfs4_stateid *stateid,
				  unsigned long pagemod_limit)
{
	struct nfs_delegation *delegation;
	const struct cred *oldcred = NULL;

	rcu_read_lock();
	delegation = rcu_dereference(NFS_I(inode)->delegation);
	if (delegation != NULL) {
		spin_lock(&delegation->lock);
		if (delegation->inode != NULL) {
			nfs4_stateid_copy(&delegation->stateid, stateid);
			delegation->type = type;
			delegation->pagemod_limit = pagemod_limit;
			oldcred = delegation->cred;
			delegation->cred = get_cred(cred);
			clear_bit(NFS_DELEGATION_NEED_RECLAIM,
				  &delegation->flags);
			spin_unlock(&delegation->lock);
			rcu_read_unlock();
			put_cred(oldcred);
			trace_nfs4_reclaim_delegation(inode, type);
			return;
		}
		/* We appear to have raced with a delegation return. */
		spin_unlock(&delegation->lock);
	}
	rcu_read_unlock();
	nfs_inode_set_delegation(inode, cred, type, stateid, pagemod_limit);
}