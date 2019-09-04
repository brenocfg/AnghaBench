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
struct xfs_sb {scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; scalar_t__ sb_pquotino; int sb_qflags; } ;

/* Variables and functions */
 scalar_t__ NULLFSINO ; 
 int XFS_GQUOTA_CHKD ; 
 int XFS_GQUOTA_ENFD ; 
 int XFS_OQUOTA_CHKD ; 
 int XFS_OQUOTA_ENFD ; 
 int XFS_PQUOTA_ACCT ; 
 int XFS_PQUOTA_CHKD ; 
 int XFS_PQUOTA_ENFD ; 
 scalar_t__ xfs_sb_version_has_pquotino (struct xfs_sb*) ; 

void
xfs_sb_quota_from_disk(struct xfs_sb *sbp)
{
	/*
	 * older mkfs doesn't initialize quota inodes to NULLFSINO. This
	 * leads to in-core values having two different values for a quota
	 * inode to be invalid: 0 and NULLFSINO. Change it to a single value
	 * NULLFSINO.
	 *
	 * Note that this change affect only the in-core values. These
	 * values are not written back to disk unless any quota information
	 * is written to the disk. Even in that case, sb_pquotino field is
	 * not written to disk unless the superblock supports pquotino.
	 */
	if (sbp->sb_uquotino == 0)
		sbp->sb_uquotino = NULLFSINO;
	if (sbp->sb_gquotino == 0)
		sbp->sb_gquotino = NULLFSINO;
	if (sbp->sb_pquotino == 0)
		sbp->sb_pquotino = NULLFSINO;

	/*
	 * We need to do these manipilations only if we are working
	 * with an older version of on-disk superblock.
	 */
	if (xfs_sb_version_has_pquotino(sbp))
		return;

	if (sbp->sb_qflags & XFS_OQUOTA_ENFD)
		sbp->sb_qflags |= (sbp->sb_qflags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_ENFD : XFS_GQUOTA_ENFD;
	if (sbp->sb_qflags & XFS_OQUOTA_CHKD)
		sbp->sb_qflags |= (sbp->sb_qflags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_CHKD : XFS_GQUOTA_CHKD;
	sbp->sb_qflags &= ~(XFS_OQUOTA_ENFD | XFS_OQUOTA_CHKD);

	if (sbp->sb_qflags & XFS_PQUOTA_ACCT &&
	    sbp->sb_gquotino != NULLFSINO)  {
		/*
		 * In older version of superblock, on-disk superblock only
		 * has sb_gquotino, and in-core superblock has both sb_gquotino
		 * and sb_pquotino. But, only one of them is supported at any
		 * point of time. So, if PQUOTA is set in disk superblock,
		 * copy over sb_gquotino to sb_pquotino.  The NULLFSINO test
		 * above is to make sure we don't do this twice and wipe them
		 * both out!
		 */
		sbp->sb_pquotino = sbp->sb_gquotino;
		sbp->sb_gquotino = NULLFSINO;
	}
}