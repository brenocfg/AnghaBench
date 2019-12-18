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
struct pnfs_layoutdriver_type {int /*<<< orphan*/  (* add_lseg ) (struct pnfs_layout_hdr*,struct pnfs_layout_segment*,struct list_head*) ;} ;
struct pnfs_layout_segment {int dummy; } ;
struct pnfs_layout_hdr {struct inode* plh_inode; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct pnfs_layoutdriver_type* pnfs_curr_ld; } ;

/* Variables and functions */
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  pnfs_generic_layout_insert_lseg (struct pnfs_layout_hdr*,struct pnfs_layout_segment*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  pnfs_lseg_no_merge ; 
 int /*<<< orphan*/  pnfs_lseg_range_is_after ; 
 int /*<<< orphan*/  stub1 (struct pnfs_layout_hdr*,struct pnfs_layout_segment*,struct list_head*) ; 

__attribute__((used)) static void
pnfs_layout_insert_lseg(struct pnfs_layout_hdr *lo,
		   struct pnfs_layout_segment *lseg,
		   struct list_head *free_me)
{
	struct inode *inode = lo->plh_inode;
	struct pnfs_layoutdriver_type *ld = NFS_SERVER(inode)->pnfs_curr_ld;

	if (ld->add_lseg != NULL)
		ld->add_lseg(lo, lseg, free_me);
	else
		pnfs_generic_layout_insert_lseg(lo, lseg,
				pnfs_lseg_range_is_after,
				pnfs_lseg_no_merge,
				free_me);
}