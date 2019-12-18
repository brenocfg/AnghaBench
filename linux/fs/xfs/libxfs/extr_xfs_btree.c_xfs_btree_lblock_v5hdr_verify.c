#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_3__ m_sb; } ;
struct xfs_buf {int /*<<< orphan*/  b_bn; struct xfs_mount* b_mount; } ;
struct TYPE_5__ {scalar_t__ bb_blkno; int /*<<< orphan*/  bb_owner; int /*<<< orphan*/  bb_uuid; } ;
struct TYPE_4__ {TYPE_2__ l; } ;
struct xfs_btree_block {TYPE_1__ bb_u; } ;

/* Variables and functions */
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 scalar_t__ XFS_RMAP_OWN_UNKNOWN ; 
 int /*<<< orphan*/ * __this_address ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (TYPE_3__*) ; 

xfs_failaddr_t
xfs_btree_lblock_v5hdr_verify(
	struct xfs_buf		*bp,
	uint64_t		owner)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return __this_address;
	if (!uuid_equal(&block->bb_u.l.bb_uuid, &mp->m_sb.sb_meta_uuid))
		return __this_address;
	if (block->bb_u.l.bb_blkno != cpu_to_be64(bp->b_bn))
		return __this_address;
	if (owner != XFS_RMAP_OWN_UNKNOWN &&
	    be64_to_cpu(block->bb_u.l.bb_owner) != owner)
		return __this_address;
	return NULL;
}