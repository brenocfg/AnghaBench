#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_buf {struct xfs_mount* b_mount; } ;
struct TYPE_3__ {int /*<<< orphan*/  bb_lsn; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct xfs_btree_block {TYPE_2__ bb_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_SBLOCK_CRC_OFF ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int xfs_buf_verify_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_check_lsn (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 

bool
xfs_btree_sblock_verify_crc(
	struct xfs_buf		*bp)
{
	struct xfs_btree_block  *block = XFS_BUF_TO_BLOCK(bp);
	struct xfs_mount	*mp = bp->b_mount;

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		if (!xfs_log_check_lsn(mp, be64_to_cpu(block->bb_u.s.bb_lsn)))
			return false;
		return xfs_buf_verify_cksum(bp, XFS_BTREE_SBLOCK_CRC_OFF);
	}

	return true;
}