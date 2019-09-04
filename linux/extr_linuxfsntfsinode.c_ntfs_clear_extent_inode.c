#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr_extents; int /*<<< orphan*/  mft_no; } ;
typedef  TYPE_1__ ntfs_inode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NInoAttr (TYPE_1__*) ; 
 int /*<<< orphan*/  __ntfs_clear_inode (TYPE_1__*) ; 
 int /*<<< orphan*/  ntfs_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntfs_destroy_extent_inode (TYPE_1__*) ; 

void ntfs_clear_extent_inode(ntfs_inode *ni)
{
	ntfs_debug("Entering for inode 0x%lx.", ni->mft_no);

	BUG_ON(NInoAttr(ni));
	BUG_ON(ni->nr_extents != -1);

#ifdef NTFS_RW
	if (NInoDirty(ni)) {
		if (!is_bad_inode(VFS_I(ni->ext.base_ntfs_ino)))
			ntfs_error(ni->vol->sb, "Clearing dirty extent inode!  "
					"Losing data!  This is a BUG!!!");
		// FIXME:  Do something!!!
	}
#endif /* NTFS_RW */

	__ntfs_clear_inode(ni);

	/* Bye, bye... */
	ntfs_destroy_extent_inode(ni);
}