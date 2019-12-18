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
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_inode {int /*<<< orphan*/  i_mount; } ;
struct iomap {int /*<<< orphan*/  dax_dev; int /*<<< orphan*/  bdev; void* length; void* offset; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMAP_HOLE ; 
 int /*<<< orphan*/  IOMAP_NULL_ADDR ; 
 int /*<<< orphan*/  VFS_I (struct xfs_inode*) ; 
 void* XFS_FSB_TO_B (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_find_bdev_for_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_find_daxdev_for_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_hole_to_iomap(
	struct xfs_inode	*ip,
	struct iomap		*iomap,
	xfs_fileoff_t		offset_fsb,
	xfs_fileoff_t		end_fsb)
{
	iomap->addr = IOMAP_NULL_ADDR;
	iomap->type = IOMAP_HOLE;
	iomap->offset = XFS_FSB_TO_B(ip->i_mount, offset_fsb);
	iomap->length = XFS_FSB_TO_B(ip->i_mount, end_fsb - offset_fsb);
	iomap->bdev = xfs_find_bdev_for_inode(VFS_I(ip));
	iomap->dax_dev = xfs_find_daxdev_for_inode(VFS_I(ip));
}