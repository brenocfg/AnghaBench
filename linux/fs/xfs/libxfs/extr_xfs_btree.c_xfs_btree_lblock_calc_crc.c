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
struct TYPE_8__ {int /*<<< orphan*/  li_lsn; } ;
struct xfs_buf_log_item {TYPE_4__ bli_item; } ;
struct xfs_buf {TYPE_1__* b_mount; struct xfs_buf_log_item* b_log_item; } ;
struct TYPE_6__ {int /*<<< orphan*/  bb_lsn; } ;
struct TYPE_7__ {TYPE_2__ l; } ;
struct xfs_btree_block {TYPE_3__ bb_u; } ;
struct TYPE_5__ {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_BTREE_LBLOCK_CRC_OFF ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_update_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 

void
xfs_btree_lblock_calc_crc(
	struct xfs_buf		*bp)
{
	struct xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	if (!xfs_sb_version_hascrc(&bp->b_mount->m_sb))
		return;
	if (bip)
		block->bb_u.l.bb_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	xfs_buf_update_cksum(bp, XFS_BTREE_LBLOCK_CRC_OFF);
}