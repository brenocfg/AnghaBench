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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_segs; int /*<<< orphan*/  plh_refcount; struct inode* plh_inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_detach_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_free_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  pnfs_layoutreturn_before_put_layout_hdr (struct pnfs_layout_hdr*) ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
pnfs_put_layout_hdr(struct pnfs_layout_hdr *lo)
{
	struct inode *inode;

	if (!lo)
		return;
	inode = lo->plh_inode;
	pnfs_layoutreturn_before_put_layout_hdr(lo);

	if (refcount_dec_and_lock(&lo->plh_refcount, &inode->i_lock)) {
		if (!list_empty(&lo->plh_segs))
			WARN_ONCE(1, "NFS: BUG unfreed layout segments.\n");
		pnfs_detach_layout_hdr(lo);
		spin_unlock(&inode->i_lock);
		pnfs_free_layout_hdr(lo);
	}
}