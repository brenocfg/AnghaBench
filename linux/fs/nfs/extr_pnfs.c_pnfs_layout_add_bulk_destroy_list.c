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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_bulk_destroy; } ;
struct list_head {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_get_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pnfs_layout_add_bulk_destroy_list(struct inode *inode,
		struct list_head *layout_list)
{
	struct pnfs_layout_hdr *lo;
	bool ret = false;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	if (lo != NULL && list_empty(&lo->plh_bulk_destroy)) {
		pnfs_get_layout_hdr(lo);
		list_add(&lo->plh_bulk_destroy, layout_list);
		ret = true;
	}
	spin_unlock(&inode->i_lock);
	return ret;
}