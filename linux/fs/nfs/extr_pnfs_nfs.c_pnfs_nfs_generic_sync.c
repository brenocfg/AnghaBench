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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSH_SYNC ; 
 int nfs_commit_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int pnfs_layoutcommit_inode (struct inode*,int) ; 
 int /*<<< orphan*/  pnfs_layoutcommit_outstanding (struct inode*) ; 

int
pnfs_nfs_generic_sync(struct inode *inode, bool datasync)
{
	int ret;

	if (!pnfs_layoutcommit_outstanding(inode))
		return 0;
	ret = nfs_commit_inode(inode, FLUSH_SYNC);
	if (ret < 0)
		return ret;
	if (datasync)
		return 0;
	return pnfs_layoutcommit_inode(inode, true);
}