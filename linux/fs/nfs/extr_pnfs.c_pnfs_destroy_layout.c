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
struct pnfs_layout_hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_lock; } ;
struct nfs_inode {TYPE_1__ vfs_inode; struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_LAYOUT_RO_FAILED ; 
 int /*<<< orphan*/  NFS_LAYOUT_RW_FAILED ; 
 int /*<<< orphan*/  nfs_commit_inode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_free_lseg_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_get_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_layout_clear_fail_bit (struct pnfs_layout_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_mark_layout_stateid_invalid (struct pnfs_layout_hdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_list ; 

void
pnfs_destroy_layout(struct nfs_inode *nfsi)
{
	struct pnfs_layout_hdr *lo;
	LIST_HEAD(tmp_list);

	spin_lock(&nfsi->vfs_inode.i_lock);
	lo = nfsi->layout;
	if (lo) {
		pnfs_get_layout_hdr(lo);
		pnfs_mark_layout_stateid_invalid(lo, &tmp_list);
		pnfs_layout_clear_fail_bit(lo, NFS_LAYOUT_RO_FAILED);
		pnfs_layout_clear_fail_bit(lo, NFS_LAYOUT_RW_FAILED);
		spin_unlock(&nfsi->vfs_inode.i_lock);
		pnfs_free_lseg_list(&tmp_list);
		nfs_commit_inode(&nfsi->vfs_inode, 0);
		pnfs_put_layout_hdr(lo);
	} else
		spin_unlock(&nfsi->vfs_inode.i_lock);
}