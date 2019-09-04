#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_btnum_t ;
struct TYPE_8__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_4__ m_sb; } ;
struct xfs_buf {int /*<<< orphan*/  b_bn; } ;
struct xfs_btree_cur {TYPE_1__* bc_ops; int /*<<< orphan*/  bc_btnum; struct xfs_mount* bc_mp; } ;
struct TYPE_6__ {scalar_t__ bb_blkno; scalar_t__ bb_leftsib; scalar_t__ bb_rightsib; int /*<<< orphan*/  bb_uuid; } ;
struct TYPE_7__ {TYPE_2__ s; } ;
struct xfs_btree_block {scalar_t__ bb_magic; TYPE_3__ bb_u; int /*<<< orphan*/  bb_numrecs; int /*<<< orphan*/  bb_level; } ;
struct TYPE_5__ {int (* get_maxrecs ) (struct xfs_btree_cur*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NULLAGBLOCK ; 
 int /*<<< orphan*/  XFS_BUF_DADDR_NULL ; 
 int /*<<< orphan*/ * __this_address ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int stub1 (struct xfs_btree_cur*,int) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_btree_check_sptr (struct xfs_btree_cur*,scalar_t__,int) ; 
 scalar_t__ xfs_btree_magic (int,int /*<<< orphan*/ ) ; 
 int xfs_sb_version_hascrc (TYPE_4__*) ; 

xfs_failaddr_t
__xfs_btree_check_sblock(
	struct xfs_btree_cur	*cur,
	struct xfs_btree_block	*block,
	int			level,
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = cur->bc_mp;
	xfs_btnum_t		btnum = cur->bc_btnum;
	int			crc = xfs_sb_version_hascrc(&mp->m_sb);

	if (crc) {
		if (!uuid_equal(&block->bb_u.s.bb_uuid, &mp->m_sb.sb_meta_uuid))
			return __this_address;
		if (block->bb_u.s.bb_blkno !=
		    cpu_to_be64(bp ? bp->b_bn : XFS_BUF_DADDR_NULL))
			return __this_address;
	}

	if (be32_to_cpu(block->bb_magic) != xfs_btree_magic(crc, btnum))
		return __this_address;
	if (be16_to_cpu(block->bb_level) != level)
		return __this_address;
	if (be16_to_cpu(block->bb_numrecs) >
	    cur->bc_ops->get_maxrecs(cur, level))
		return __this_address;
	if (block->bb_u.s.bb_leftsib != cpu_to_be32(NULLAGBLOCK) &&
	    !xfs_btree_check_sptr(cur, be32_to_cpu(block->bb_u.s.bb_leftsib),
			level + 1))
		return __this_address;
	if (block->bb_u.s.bb_rightsib != cpu_to_be32(NULLAGBLOCK) &&
	    !xfs_btree_check_sptr(cur, be32_to_cpu(block->bb_u.s.bb_rightsib),
			level + 1))
		return __this_address;

	return NULL;
}