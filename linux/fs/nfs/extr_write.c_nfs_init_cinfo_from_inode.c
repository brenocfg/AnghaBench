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
struct nfs_commit_info {int /*<<< orphan*/ * completion_ops; int /*<<< orphan*/ * dreq; int /*<<< orphan*/  ds; int /*<<< orphan*/ * mds; struct inode* inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_info; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  nfs_commit_completion_ops ; 
 int /*<<< orphan*/  pnfs_get_ds_info (struct inode*) ; 

__attribute__((used)) static void nfs_init_cinfo_from_inode(struct nfs_commit_info *cinfo,
				      struct inode *inode)
{
	cinfo->inode = inode;
	cinfo->mds = &NFS_I(inode)->commit_info;
	cinfo->ds = pnfs_get_ds_info(inode);
	cinfo->dreq = NULL;
	cinfo->completion_ops = &nfs_commit_completion_ops;
}