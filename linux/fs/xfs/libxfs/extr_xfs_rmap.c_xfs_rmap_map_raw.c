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
struct xfs_rmap_irec {int rm_flags; int /*<<< orphan*/  rm_blockcount; int /*<<< orphan*/  rm_startblock; int /*<<< orphan*/  rm_owner; int /*<<< orphan*/  rm_offset; } ;
struct xfs_owner_info {int /*<<< orphan*/  oi_flags; int /*<<< orphan*/  oi_offset; int /*<<< orphan*/  oi_owner; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_OWNER_INFO_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_OWNER_INFO_BMBT_BLOCK ; 
 int XFS_RMAP_ATTR_FORK ; 
 int XFS_RMAP_BMBT_BLOCK ; 
 scalar_t__ XFS_RMAP_NON_INODE_OWNER (int /*<<< orphan*/ ) ; 
 int XFS_RMAP_UNWRITTEN ; 
 int xfs_rmap_map (struct xfs_btree_cur*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_owner_info*) ; 
 int xfs_rmap_map_shared (struct xfs_btree_cur*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_owner_info*) ; 

int
xfs_rmap_map_raw(
	struct xfs_btree_cur	*cur,
	struct xfs_rmap_irec	*rmap)
{
	struct xfs_owner_info	oinfo;

	oinfo.oi_owner = rmap->rm_owner;
	oinfo.oi_offset = rmap->rm_offset;
	oinfo.oi_flags = 0;
	if (rmap->rm_flags & XFS_RMAP_ATTR_FORK)
		oinfo.oi_flags |= XFS_OWNER_INFO_ATTR_FORK;
	if (rmap->rm_flags & XFS_RMAP_BMBT_BLOCK)
		oinfo.oi_flags |= XFS_OWNER_INFO_BMBT_BLOCK;

	if (rmap->rm_flags || XFS_RMAP_NON_INODE_OWNER(rmap->rm_owner))
		return xfs_rmap_map(cur, rmap->rm_startblock,
				rmap->rm_blockcount,
				rmap->rm_flags & XFS_RMAP_UNWRITTEN,
				&oinfo);

	return xfs_rmap_map_shared(cur, rmap->rm_startblock,
			rmap->rm_blockcount,
			rmap->rm_flags & XFS_RMAP_UNWRITTEN,
			&oinfo);
}