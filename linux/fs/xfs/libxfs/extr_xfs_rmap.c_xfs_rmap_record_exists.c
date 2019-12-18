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
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agblock_t ;
typedef  scalar_t__ uint64_t ;
struct xfs_rmap_irec {scalar_t__ rm_owner; scalar_t__ rm_startblock; scalar_t__ rm_blockcount; } ;
struct xfs_owner_info {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 unsigned int XFS_RMAP_BMBT_BLOCK ; 
 scalar_t__ XFS_RMAP_NON_INODE_OWNER (scalar_t__) ; 
 int /*<<< orphan*/  xfs_owner_info_unpack (struct xfs_owner_info const*,scalar_t__*,scalar_t__*,unsigned int*) ; 
 int xfs_rmap_get_rec (struct xfs_btree_cur*,struct xfs_rmap_irec*,int*) ; 
 int xfs_rmap_lookup_le (struct xfs_btree_cur*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,unsigned int,int*) ; 

int
xfs_rmap_record_exists(
	struct xfs_btree_cur		*cur,
	xfs_agblock_t			bno,
	xfs_extlen_t			len,
	const struct xfs_owner_info	*oinfo,
	bool				*has_rmap)
{
	uint64_t			owner;
	uint64_t			offset;
	unsigned int			flags;
	int				has_record;
	struct xfs_rmap_irec		irec;
	int				error;

	xfs_owner_info_unpack(oinfo, &owner, &offset, &flags);
	ASSERT(XFS_RMAP_NON_INODE_OWNER(owner) ||
	       (flags & XFS_RMAP_BMBT_BLOCK));

	error = xfs_rmap_lookup_le(cur, bno, len, owner, offset, flags,
			&has_record);
	if (error)
		return error;
	if (!has_record) {
		*has_rmap = false;
		return 0;
	}

	error = xfs_rmap_get_rec(cur, &irec, &has_record);
	if (error)
		return error;
	if (!has_record) {
		*has_rmap = false;
		return 0;
	}

	*has_rmap = (irec.rm_owner == owner && irec.rm_startblock <= bno &&
		     irec.rm_startblock + irec.rm_blockcount >= bno + len);
	return 0;
}