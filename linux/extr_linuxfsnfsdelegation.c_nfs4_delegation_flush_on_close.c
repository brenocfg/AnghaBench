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
struct nfs_inode {int /*<<< orphan*/  nrequests; int /*<<< orphan*/  delegation; } ;
struct nfs_delegation {int type; scalar_t__ pagemod_limit; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 struct nfs_inode* NFS_I (struct inode const*) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool nfs4_delegation_flush_on_close(const struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_delegation *delegation;
	bool ret = true;

	rcu_read_lock();
	delegation = rcu_dereference(nfsi->delegation);
	if (delegation == NULL || !(delegation->type & FMODE_WRITE))
		goto out;
	if (atomic_long_read(&nfsi->nrequests) < delegation->pagemod_limit)
		ret = false;
out:
	rcu_read_unlock();
	return ret;
}