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
struct xfs_sb {int dummy; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_dsb {scalar_t__ sb_magicnum; scalar_t__ sb_crc; int /*<<< orphan*/  sb_versionnum; } ;
struct xfs_buf {scalar_t__ b_bn; struct xfs_mount* b_mount; } ;

/* Variables and functions */
 int EFSBADCRC ; 
 int EFSCORRUPTED ; 
 struct xfs_dsb* XFS_BUF_TO_SBP (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_SB_CRC_OFF ; 
 scalar_t__ XFS_SB_DADDR ; 
 int /*<<< orphan*/  XFS_SB_MAGIC ; 
 int XFS_SB_VERSION_5 ; 
 int XFS_SB_VERSION_NUMBITS ; 
 int /*<<< orphan*/  __this_address ; 
 int /*<<< orphan*/  __xfs_sb_from_disk (struct xfs_sb*,struct xfs_dsb*,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_ioerror (struct xfs_buf*,int) ; 
 int /*<<< orphan*/  xfs_buf_verify_cksum (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int xfs_validate_sb_common (struct xfs_mount*,struct xfs_buf*,struct xfs_sb*) ; 
 int xfs_validate_sb_read (struct xfs_mount*,struct xfs_sb*) ; 
 int /*<<< orphan*/  xfs_verifier_error (struct xfs_buf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_sb_read_verify(
	struct xfs_buf		*bp)
{
	struct xfs_sb		sb;
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_dsb		*dsb = XFS_BUF_TO_SBP(bp);
	int			error;

	/*
	 * open code the version check to avoid needing to convert the entire
	 * superblock from disk order just to check the version number
	 */
	if (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC) &&
	    (((be16_to_cpu(dsb->sb_versionnum) & XFS_SB_VERSION_NUMBITS) ==
						XFS_SB_VERSION_5) ||
	     dsb->sb_crc != 0)) {

		if (!xfs_buf_verify_cksum(bp, XFS_SB_CRC_OFF)) {
			/* Only fail bad secondaries on a known V5 filesystem */
			if (bp->b_bn == XFS_SB_DADDR ||
			    xfs_sb_version_hascrc(&mp->m_sb)) {
				error = -EFSBADCRC;
				goto out_error;
			}
		}
	}

	/*
	 * Check all the superblock fields.  Don't byteswap the xquota flags
	 * because _verify_common checks the on-disk values.
	 */
	__xfs_sb_from_disk(&sb, XFS_BUF_TO_SBP(bp), false);
	error = xfs_validate_sb_common(mp, bp, &sb);
	if (error)
		goto out_error;
	error = xfs_validate_sb_read(mp, &sb);

out_error:
	if (error == -EFSCORRUPTED || error == -EFSBADCRC)
		xfs_verifier_error(bp, error, __this_address);
	else if (error)
		xfs_buf_ioerror(bp, error);
}