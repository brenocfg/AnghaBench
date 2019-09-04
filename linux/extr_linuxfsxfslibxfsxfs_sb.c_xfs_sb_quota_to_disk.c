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
typedef  int uint16_t ;
struct xfs_sb {int sb_qflags; scalar_t__ sb_uquotino; scalar_t__ sb_gquotino; scalar_t__ sb_pquotino; } ;
struct xfs_dsb {void* sb_pquotino; void* sb_gquotino; void* sb_qflags; void* sb_uquotino; } ;

/* Variables and functions */
 scalar_t__ NULLFSINO ; 
 int XFS_GQUOTA_ACCT ; 
 int XFS_GQUOTA_CHKD ; 
 int XFS_GQUOTA_ENFD ; 
 int XFS_OQUOTA_CHKD ; 
 int XFS_OQUOTA_ENFD ; 
 int XFS_PQUOTA_ACCT ; 
 int XFS_PQUOTA_CHKD ; 
 int XFS_PQUOTA_ENFD ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 scalar_t__ xfs_sb_version_has_pquotino (struct xfs_sb*) ; 

__attribute__((used)) static void
xfs_sb_quota_to_disk(
	struct xfs_dsb	*to,
	struct xfs_sb	*from)
{
	uint16_t	qflags = from->sb_qflags;

	to->sb_uquotino = cpu_to_be64(from->sb_uquotino);
	if (xfs_sb_version_has_pquotino(from)) {
		to->sb_qflags = cpu_to_be16(from->sb_qflags);
		to->sb_gquotino = cpu_to_be64(from->sb_gquotino);
		to->sb_pquotino = cpu_to_be64(from->sb_pquotino);
		return;
	}

	/*
	 * The in-core version of sb_qflags do not have XFS_OQUOTA_*
	 * flags, whereas the on-disk version does.  So, convert incore
	 * XFS_{PG}QUOTA_* flags to on-disk XFS_OQUOTA_* flags.
	 */
	qflags &= ~(XFS_PQUOTA_ENFD | XFS_PQUOTA_CHKD |
			XFS_GQUOTA_ENFD | XFS_GQUOTA_CHKD);

	if (from->sb_qflags &
			(XFS_PQUOTA_ENFD | XFS_GQUOTA_ENFD))
		qflags |= XFS_OQUOTA_ENFD;
	if (from->sb_qflags &
			(XFS_PQUOTA_CHKD | XFS_GQUOTA_CHKD))
		qflags |= XFS_OQUOTA_CHKD;
	to->sb_qflags = cpu_to_be16(qflags);

	/*
	 * GQUOTINO and PQUOTINO cannot be used together in versions
	 * of superblock that do not have pquotino. from->sb_flags
	 * tells us which quota is active and should be copied to
	 * disk. If neither are active, we should NULL the inode.
	 *
	 * In all cases, the separate pquotino must remain 0 because it
	 * it beyond the "end" of the valid non-pquotino superblock.
	 */
	if (from->sb_qflags & XFS_GQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(from->sb_gquotino);
	else if (from->sb_qflags & XFS_PQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(from->sb_pquotino);
	else {
		/*
		 * We can't rely on just the fields being logged to tell us
		 * that it is safe to write NULLFSINO - we should only do that
		 * if quotas are not actually enabled. Hence only write
		 * NULLFSINO if both in-core quota inodes are NULL.
		 */
		if (from->sb_gquotino == NULLFSINO &&
		    from->sb_pquotino == NULLFSINO)
			to->sb_gquotino = cpu_to_be64(NULLFSINO);
	}

	to->sb_pquotino = 0;
}