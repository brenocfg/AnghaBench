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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_files; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_access_zap_cache (struct inode*) ; 
 int /*<<< orphan*/  nfs_fscache_clear_inode (struct inode*) ; 
 int nfs_have_writebacks (struct inode*) ; 
 int /*<<< orphan*/  nfs_zap_acl_cache (struct inode*) ; 

void nfs_clear_inode(struct inode *inode)
{
	/*
	 * The following should never happen...
	 */
	WARN_ON_ONCE(nfs_have_writebacks(inode));
	WARN_ON_ONCE(!list_empty(&NFS_I(inode)->open_files));
	nfs_zap_acl_cache(inode);
	nfs_access_zap_cache(inode);
	nfs_fscache_clear_inode(inode);
}