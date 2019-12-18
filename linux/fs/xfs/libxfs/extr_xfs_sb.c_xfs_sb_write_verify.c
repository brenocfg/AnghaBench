#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_sb {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  li_lsn; } ;
struct xfs_buf_log_item {TYPE_1__ bli_item; } ;
struct xfs_buf {struct xfs_buf_log_item* b_log_item; struct xfs_mount* b_mount; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb_lsn; } ;

/* Variables and functions */
 TYPE_2__* XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_SB_CRC_OFF ; 
 int /*<<< orphan*/  __this_address ; 
 int /*<<< orphan*/  __xfs_sb_from_disk (struct xfs_sb*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_update_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int xfs_validate_sb_common (struct xfs_mount*,struct xfs_buf*,struct xfs_sb*) ; 
 int xfs_validate_sb_write (struct xfs_mount*,struct xfs_buf*,struct xfs_sb*) ; 
 int /*<<< orphan*/  xfs_verifier_error (struct xfs_buf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_sb_write_verify(
	struct xfs_buf		*bp)
{
	struct xfs_sb		sb;
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_buf_log_item	*bip = bp->b_log_item;
	int			error;

	/*
	 * Check all the superblock fields.  Don't byteswap the xquota flags
	 * because _verify_common checks the on-disk values.
	 */
	__xfs_sb_from_disk(&sb, XFS_BUF_TO_SBP(bp), false);
	error = xfs_validate_sb_common(mp, bp, &sb);
	if (error)
		goto out_error;
	error = xfs_validate_sb_write(mp, bp, &sb);
	if (error)
		goto out_error;

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return;

	if (bip)
		XFS_BUF_TO_SBP(bp)->sb_lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_SB_CRC_OFF);
	return;

out_error:
	xfs_verifier_error(bp, error, __this_address);
}