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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_block_lgets; } ;
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_mapping; } ;
struct TYPE_2__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int _pnfs_return_layout (struct inode*) ; 
 int /*<<< orphan*/  filemap_fdatawait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_get_layout_hdr (struct pnfs_layout_hdr*) ; 
 int pnfs_layoutcommit_inode (struct inode*,int) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
pnfs_commit_and_return_layout(struct inode *inode)
{
	struct pnfs_layout_hdr *lo;
	int ret;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	if (lo == NULL) {
		spin_unlock(&inode->i_lock);
		return 0;
	}
	pnfs_get_layout_hdr(lo);
	/* Block new layoutgets and read/write to ds */
	lo->plh_block_lgets++;
	spin_unlock(&inode->i_lock);
	filemap_fdatawait(inode->i_mapping);
	ret = pnfs_layoutcommit_inode(inode, true);
	if (ret == 0)
		ret = _pnfs_return_layout(inode);
	spin_lock(&inode->i_lock);
	lo->plh_block_lgets--;
	spin_unlock(&inode->i_lock);
	pnfs_put_layout_hdr(lo);
	return ret;
}