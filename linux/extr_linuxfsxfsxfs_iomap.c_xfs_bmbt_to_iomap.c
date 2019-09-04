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
struct xfs_mount {int dummy; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; scalar_t__ br_state; int /*<<< orphan*/  br_blockcount; int /*<<< orphan*/  br_startoff; } ;
struct iomap {int /*<<< orphan*/  dax_dev; int /*<<< orphan*/  bdev; void* length; void* offset; int /*<<< orphan*/  type; void* addr; } ;

/* Variables and functions */
 void* BBTOB (int /*<<< orphan*/ ) ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int /*<<< orphan*/  IOMAP_DELALLOC ; 
 int /*<<< orphan*/  IOMAP_HOLE ; 
 int /*<<< orphan*/  IOMAP_MAPPED ; 
 void* IOMAP_NULL_ADDR ; 
 int /*<<< orphan*/  IOMAP_UNWRITTEN ; 
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 scalar_t__ XFS_EXT_UNWRITTEN ; 
 void* XFS_FSB_TO_B (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_find_bdev_for_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_find_daxdev_for_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_fsb_to_db (struct xfs_inode*,scalar_t__) ; 

void
xfs_bmbt_to_iomap(
	struct xfs_inode	*ip,
	struct iomap		*iomap,
	struct xfs_bmbt_irec	*imap)
{
	struct xfs_mount	*mp = ip->i_mount;

	if (imap->br_startblock == HOLESTARTBLOCK) {
		iomap->addr = IOMAP_NULL_ADDR;
		iomap->type = IOMAP_HOLE;
	} else if (imap->br_startblock == DELAYSTARTBLOCK) {
		iomap->addr = IOMAP_NULL_ADDR;
		iomap->type = IOMAP_DELALLOC;
	} else {
		iomap->addr = BBTOB(xfs_fsb_to_db(ip, imap->br_startblock));
		if (imap->br_state == XFS_EXT_UNWRITTEN)
			iomap->type = IOMAP_UNWRITTEN;
		else
			iomap->type = IOMAP_MAPPED;
	}
	iomap->offset = XFS_FSB_TO_B(mp, imap->br_startoff);
	iomap->length = XFS_FSB_TO_B(mp, imap->br_blockcount);
	iomap->bdev = xfs_find_bdev_for_inode(VFS_I(ip));
	iomap->dax_dev = xfs_find_daxdev_for_inode(VFS_I(ip));
}