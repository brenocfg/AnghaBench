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
typedef  scalar_t__ xfs_failaddr_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsn; } ;
struct xfs_dir3_leaf_hdr {TYPE_1__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  li_lsn; } ;
struct xfs_buf_log_item {TYPE_2__ bli_item; } ;
struct xfs_buf {struct xfs_dir3_leaf_hdr* b_addr; struct xfs_buf_log_item* b_log_item; TYPE_3__* b_target; } ;
struct TYPE_6__ {struct xfs_mount* bt_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_DIR3_LEAF_CRC_OFF ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_update_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dir3_leaf_verify (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_verifier_error (struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
__write_verify(
	struct xfs_buf  *bp,
	uint16_t	magic)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;
	struct xfs_buf_log_item	*bip = bp->b_log_item;
	struct xfs_dir3_leaf_hdr *hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_dir3_leaf_verify(bp, magic);
	if (fa) {
		xfs_verifier_error(bp, -EFSCORRUPTED, fa);
		return;
	}

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return;

	if (bip)
		hdr3->info.lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_DIR3_LEAF_CRC_OFF);
}