#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_agblock_t ;
typedef  void* uint64_t ;
struct xfs_rmap_irec {int /*<<< orphan*/  rm_flags; int /*<<< orphan*/  rm_offset; int /*<<< orphan*/  rm_owner; int /*<<< orphan*/  rm_blockcount; int /*<<< orphan*/  rm_startblock; } ;
struct TYPE_7__ {unsigned int rm_flags; scalar_t__ rm_blockcount; void* rm_offset; void* rm_owner; int /*<<< orphan*/  rm_startblock; } ;
struct xfs_find_left_neighbor_info {int* stat; TYPE_3__ high; struct xfs_rmap_irec* irec; } ;
struct TYPE_5__ {int /*<<< orphan*/  agno; } ;
struct TYPE_6__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 int ECANCELED ; 
 unsigned int XFS_RMAP_BMBT_BLOCK ; 
 int /*<<< orphan*/  XFS_RMAP_NON_INODE_OWNER (void*) ; 
 int /*<<< orphan*/  trace_xfs_rmap_lookup_le_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,unsigned int) ; 
 int /*<<< orphan*/  trace_xfs_rmap_lookup_le_range_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_rmap_lookup_le_range_helper ; 
 int xfs_rmap_query_range (struct xfs_btree_cur*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,struct xfs_find_left_neighbor_info*) ; 

int
xfs_rmap_lookup_le_range(
	struct xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	uint64_t		owner,
	uint64_t		offset,
	unsigned int		flags,
	struct xfs_rmap_irec	*irec,
	int			*stat)
{
	struct xfs_find_left_neighbor_info	info;
	int			error;

	info.high.rm_startblock = bno;
	info.high.rm_owner = owner;
	if (!XFS_RMAP_NON_INODE_OWNER(owner) && !(flags & XFS_RMAP_BMBT_BLOCK))
		info.high.rm_offset = offset;
	else
		info.high.rm_offset = 0;
	info.high.rm_flags = flags;
	info.high.rm_blockcount = 0;
	*stat = 0;
	info.irec = irec;
	info.stat = stat;

	trace_xfs_rmap_lookup_le_range(cur->bc_mp,
			cur->bc_private.a.agno, bno, 0, owner, offset, flags);
	error = xfs_rmap_query_range(cur, &info.high, &info.high,
			xfs_rmap_lookup_le_range_helper, &info);
	if (error == -ECANCELED)
		error = 0;
	if (*stat)
		trace_xfs_rmap_lookup_le_range_result(cur->bc_mp,
				cur->bc_private.a.agno, irec->rm_startblock,
				irec->rm_blockcount, irec->rm_owner,
				irec->rm_offset, irec->rm_flags);
	return error;
}