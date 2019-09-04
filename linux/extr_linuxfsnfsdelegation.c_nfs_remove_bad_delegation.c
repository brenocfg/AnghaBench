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
struct nfs_delegation {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_free_delegation (struct nfs_delegation*) ; 
 struct nfs_delegation* nfs_inode_detach_delegation (struct inode*) ; 
 int /*<<< orphan*/  nfs_revoke_delegation (struct inode*,int /*<<< orphan*/  const*) ; 

void nfs_remove_bad_delegation(struct inode *inode,
		const nfs4_stateid *stateid)
{
	struct nfs_delegation *delegation;

	if (!nfs_revoke_delegation(inode, stateid))
		return;
	delegation = nfs_inode_detach_delegation(inode);
	if (delegation)
		nfs_free_delegation(delegation);
}