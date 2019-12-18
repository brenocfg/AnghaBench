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
struct nfs_delegation {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DELEGATION_RETURNING ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_delegation *
nfs_start_delegation_return_locked(struct nfs_inode *nfsi)
{
	struct nfs_delegation *ret = NULL;
	struct nfs_delegation *delegation = rcu_dereference(nfsi->delegation);

	if (delegation == NULL)
		goto out;
	spin_lock(&delegation->lock);
	if (!test_and_set_bit(NFS_DELEGATION_RETURNING, &delegation->flags))
		ret = delegation;
	spin_unlock(&delegation->lock);
out:
	return ret;
}