#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_meta_uuid; int /*<<< orphan*/  sb_lsn; int /*<<< orphan*/  sb_pquotino; int /*<<< orphan*/  sb_spino_align; int /*<<< orphan*/  sb_features_log_incompat; int /*<<< orphan*/  sb_features_incompat; int /*<<< orphan*/  sb_features_ro_compat; int /*<<< orphan*/  sb_features_compat; int /*<<< orphan*/  sb_bad_features2; int /*<<< orphan*/  sb_features2; int /*<<< orphan*/  sb_logsunit; int /*<<< orphan*/  sb_logsectsize; int /*<<< orphan*/  sb_logsectlog; int /*<<< orphan*/  sb_dirblklog; int /*<<< orphan*/  sb_width; int /*<<< orphan*/  sb_unit; int /*<<< orphan*/  sb_inoalignmt; int /*<<< orphan*/  sb_shared_vn; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_qflags; int /*<<< orphan*/  sb_gquotino; int /*<<< orphan*/  sb_uquotino; int /*<<< orphan*/  sb_frextents; int /*<<< orphan*/  sb_fdblocks; int /*<<< orphan*/  sb_ifree; int /*<<< orphan*/  sb_icount; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_inprogress; int /*<<< orphan*/  sb_rextslog; int /*<<< orphan*/  sb_agblklog; int /*<<< orphan*/  sb_inopblog; int /*<<< orphan*/  sb_inodelog; int /*<<< orphan*/  sb_sectlog; int /*<<< orphan*/  sb_blocklog; int /*<<< orphan*/  sb_fname; int /*<<< orphan*/  sb_inopblock; int /*<<< orphan*/  sb_inodesize; int /*<<< orphan*/  sb_sectsize; int /*<<< orphan*/  sb_versionnum; int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_rbmblocks; int /*<<< orphan*/  sb_agcount; int /*<<< orphan*/  sb_agblocks; int /*<<< orphan*/  sb_rextsize; int /*<<< orphan*/  sb_rsumino; int /*<<< orphan*/  sb_rbmino; int /*<<< orphan*/  sb_rootino; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_rextents; int /*<<< orphan*/  sb_rblocks; int /*<<< orphan*/  sb_dblocks; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_magicnum; } ;
typedef  TYPE_1__ xfs_dsb_t ;
struct xfs_sb {int /*<<< orphan*/  sb_meta_uuid; void* sb_lsn; void* sb_pquotino; void* sb_spino_align; scalar_t__ sb_crc; void* sb_features_log_incompat; void* sb_features_incompat; void* sb_features_ro_compat; void* sb_features_compat; void* sb_bad_features2; void* sb_features2; void* sb_logsunit; void* sb_logsectsize; int /*<<< orphan*/  sb_logsectlog; int /*<<< orphan*/  sb_dirblklog; void* sb_width; void* sb_unit; void* sb_inoalignmt; int /*<<< orphan*/  sb_shared_vn; int /*<<< orphan*/  sb_flags; void* sb_qflags; void* sb_gquotino; void* sb_uquotino; void* sb_frextents; void* sb_fdblocks; void* sb_ifree; void* sb_icount; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_inprogress; int /*<<< orphan*/  sb_rextslog; int /*<<< orphan*/  sb_agblklog; int /*<<< orphan*/  sb_inopblog; int /*<<< orphan*/  sb_inodelog; int /*<<< orphan*/  sb_sectlog; int /*<<< orphan*/  sb_blocklog; int /*<<< orphan*/  sb_fname; void* sb_inopblock; void* sb_inodesize; void* sb_sectsize; void* sb_versionnum; void* sb_logblocks; void* sb_rbmblocks; void* sb_agcount; void* sb_agblocks; void* sb_rextsize; void* sb_rsumino; void* sb_rbmino; void* sb_rootino; void* sb_logstart; int /*<<< orphan*/  sb_uuid; void* sb_rextents; void* sb_rblocks; void* sb_dblocks; void* sb_blocksize; void* sb_magicnum; } ;

/* Variables and functions */
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_quota_from_disk (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasmetauuid (struct xfs_sb*) ; 

__attribute__((used)) static void
__xfs_sb_from_disk(
	struct xfs_sb	*to,
	xfs_dsb_t	*from,
	bool		convert_xquota)
{
	to->sb_magicnum = be32_to_cpu(from->sb_magicnum);
	to->sb_blocksize = be32_to_cpu(from->sb_blocksize);
	to->sb_dblocks = be64_to_cpu(from->sb_dblocks);
	to->sb_rblocks = be64_to_cpu(from->sb_rblocks);
	to->sb_rextents = be64_to_cpu(from->sb_rextents);
	memcpy(&to->sb_uuid, &from->sb_uuid, sizeof(to->sb_uuid));
	to->sb_logstart = be64_to_cpu(from->sb_logstart);
	to->sb_rootino = be64_to_cpu(from->sb_rootino);
	to->sb_rbmino = be64_to_cpu(from->sb_rbmino);
	to->sb_rsumino = be64_to_cpu(from->sb_rsumino);
	to->sb_rextsize = be32_to_cpu(from->sb_rextsize);
	to->sb_agblocks = be32_to_cpu(from->sb_agblocks);
	to->sb_agcount = be32_to_cpu(from->sb_agcount);
	to->sb_rbmblocks = be32_to_cpu(from->sb_rbmblocks);
	to->sb_logblocks = be32_to_cpu(from->sb_logblocks);
	to->sb_versionnum = be16_to_cpu(from->sb_versionnum);
	to->sb_sectsize = be16_to_cpu(from->sb_sectsize);
	to->sb_inodesize = be16_to_cpu(from->sb_inodesize);
	to->sb_inopblock = be16_to_cpu(from->sb_inopblock);
	memcpy(&to->sb_fname, &from->sb_fname, sizeof(to->sb_fname));
	to->sb_blocklog = from->sb_blocklog;
	to->sb_sectlog = from->sb_sectlog;
	to->sb_inodelog = from->sb_inodelog;
	to->sb_inopblog = from->sb_inopblog;
	to->sb_agblklog = from->sb_agblklog;
	to->sb_rextslog = from->sb_rextslog;
	to->sb_inprogress = from->sb_inprogress;
	to->sb_imax_pct = from->sb_imax_pct;
	to->sb_icount = be64_to_cpu(from->sb_icount);
	to->sb_ifree = be64_to_cpu(from->sb_ifree);
	to->sb_fdblocks = be64_to_cpu(from->sb_fdblocks);
	to->sb_frextents = be64_to_cpu(from->sb_frextents);
	to->sb_uquotino = be64_to_cpu(from->sb_uquotino);
	to->sb_gquotino = be64_to_cpu(from->sb_gquotino);
	to->sb_qflags = be16_to_cpu(from->sb_qflags);
	to->sb_flags = from->sb_flags;
	to->sb_shared_vn = from->sb_shared_vn;
	to->sb_inoalignmt = be32_to_cpu(from->sb_inoalignmt);
	to->sb_unit = be32_to_cpu(from->sb_unit);
	to->sb_width = be32_to_cpu(from->sb_width);
	to->sb_dirblklog = from->sb_dirblklog;
	to->sb_logsectlog = from->sb_logsectlog;
	to->sb_logsectsize = be16_to_cpu(from->sb_logsectsize);
	to->sb_logsunit = be32_to_cpu(from->sb_logsunit);
	to->sb_features2 = be32_to_cpu(from->sb_features2);
	to->sb_bad_features2 = be32_to_cpu(from->sb_bad_features2);
	to->sb_features_compat = be32_to_cpu(from->sb_features_compat);
	to->sb_features_ro_compat = be32_to_cpu(from->sb_features_ro_compat);
	to->sb_features_incompat = be32_to_cpu(from->sb_features_incompat);
	to->sb_features_log_incompat =
				be32_to_cpu(from->sb_features_log_incompat);
	/* crc is only used on disk, not in memory; just init to 0 here. */
	to->sb_crc = 0;
	to->sb_spino_align = be32_to_cpu(from->sb_spino_align);
	to->sb_pquotino = be64_to_cpu(from->sb_pquotino);
	to->sb_lsn = be64_to_cpu(from->sb_lsn);
	/*
	 * sb_meta_uuid is only on disk if it differs from sb_uuid and the
	 * feature flag is set; if not set we keep it only in memory.
	 */
	if (xfs_sb_version_hasmetauuid(to))
		uuid_copy(&to->sb_meta_uuid, &from->sb_meta_uuid);
	else
		uuid_copy(&to->sb_meta_uuid, &from->sb_uuid);
	/* Convert on-disk flags to in-memory flags? */
	if (convert_xquota)
		xfs_sb_quota_from_disk(to);
}