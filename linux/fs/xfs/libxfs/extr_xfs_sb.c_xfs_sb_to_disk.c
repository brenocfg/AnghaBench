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
struct xfs_sb {int /*<<< orphan*/  sb_meta_uuid; int /*<<< orphan*/  sb_lsn; int /*<<< orphan*/  sb_spino_align; int /*<<< orphan*/  sb_features_log_incompat; int /*<<< orphan*/  sb_features_incompat; int /*<<< orphan*/  sb_features_ro_compat; int /*<<< orphan*/  sb_features_compat; int /*<<< orphan*/  sb_bad_features2; int /*<<< orphan*/  sb_features2; int /*<<< orphan*/  sb_logsunit; int /*<<< orphan*/  sb_logsectsize; int /*<<< orphan*/  sb_logsectlog; int /*<<< orphan*/  sb_dirblklog; int /*<<< orphan*/  sb_width; int /*<<< orphan*/  sb_unit; int /*<<< orphan*/  sb_inoalignmt; int /*<<< orphan*/  sb_shared_vn; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  sb_frextents; int /*<<< orphan*/  sb_fdblocks; int /*<<< orphan*/  sb_ifree; int /*<<< orphan*/  sb_icount; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_inprogress; int /*<<< orphan*/  sb_rextslog; int /*<<< orphan*/  sb_agblklog; int /*<<< orphan*/  sb_inopblog; int /*<<< orphan*/  sb_inodelog; int /*<<< orphan*/  sb_sectlog; int /*<<< orphan*/  sb_blocklog; int /*<<< orphan*/  sb_fname; int /*<<< orphan*/  sb_inopblock; int /*<<< orphan*/  sb_inodesize; int /*<<< orphan*/  sb_sectsize; int /*<<< orphan*/  sb_versionnum; int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_rbmblocks; int /*<<< orphan*/  sb_agcount; int /*<<< orphan*/  sb_agblocks; int /*<<< orphan*/  sb_rextsize; int /*<<< orphan*/  sb_rsumino; int /*<<< orphan*/  sb_rbmino; int /*<<< orphan*/  sb_rootino; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_rextents; int /*<<< orphan*/  sb_rblocks; int /*<<< orphan*/  sb_dblocks; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_magicnum; } ;
struct xfs_dsb {int /*<<< orphan*/  sb_meta_uuid; void* sb_lsn; void* sb_spino_align; void* sb_features_log_incompat; void* sb_features_incompat; void* sb_features_ro_compat; void* sb_features_compat; void* sb_bad_features2; void* sb_features2; void* sb_logsunit; void* sb_logsectsize; int /*<<< orphan*/  sb_logsectlog; int /*<<< orphan*/  sb_dirblklog; void* sb_width; void* sb_unit; void* sb_inoalignmt; int /*<<< orphan*/  sb_shared_vn; int /*<<< orphan*/  sb_flags; void* sb_frextents; void* sb_fdblocks; void* sb_ifree; void* sb_icount; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_inprogress; int /*<<< orphan*/  sb_rextslog; int /*<<< orphan*/  sb_agblklog; int /*<<< orphan*/  sb_inopblog; int /*<<< orphan*/  sb_inodelog; int /*<<< orphan*/  sb_sectlog; int /*<<< orphan*/  sb_blocklog; int /*<<< orphan*/  sb_fname; void* sb_inopblock; void* sb_inodesize; void* sb_sectsize; void* sb_versionnum; void* sb_logblocks; void* sb_rbmblocks; void* sb_agcount; void* sb_agblocks; void* sb_rextsize; void* sb_rsumino; void* sb_rbmino; void* sb_rootino; void* sb_logstart; int /*<<< orphan*/  sb_uuid; void* sb_rextents; void* sb_rblocks; void* sb_dblocks; void* sb_blocksize; void* sb_magicnum; } ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_sb_quota_to_disk (struct xfs_dsb*,struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hascrc (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasmetauuid (struct xfs_sb*) ; 

void
xfs_sb_to_disk(
	struct xfs_dsb	*to,
	struct xfs_sb	*from)
{
	xfs_sb_quota_to_disk(to, from);

	to->sb_magicnum = cpu_to_be32(from->sb_magicnum);
	to->sb_blocksize = cpu_to_be32(from->sb_blocksize);
	to->sb_dblocks = cpu_to_be64(from->sb_dblocks);
	to->sb_rblocks = cpu_to_be64(from->sb_rblocks);
	to->sb_rextents = cpu_to_be64(from->sb_rextents);
	memcpy(&to->sb_uuid, &from->sb_uuid, sizeof(to->sb_uuid));
	to->sb_logstart = cpu_to_be64(from->sb_logstart);
	to->sb_rootino = cpu_to_be64(from->sb_rootino);
	to->sb_rbmino = cpu_to_be64(from->sb_rbmino);
	to->sb_rsumino = cpu_to_be64(from->sb_rsumino);
	to->sb_rextsize = cpu_to_be32(from->sb_rextsize);
	to->sb_agblocks = cpu_to_be32(from->sb_agblocks);
	to->sb_agcount = cpu_to_be32(from->sb_agcount);
	to->sb_rbmblocks = cpu_to_be32(from->sb_rbmblocks);
	to->sb_logblocks = cpu_to_be32(from->sb_logblocks);
	to->sb_versionnum = cpu_to_be16(from->sb_versionnum);
	to->sb_sectsize = cpu_to_be16(from->sb_sectsize);
	to->sb_inodesize = cpu_to_be16(from->sb_inodesize);
	to->sb_inopblock = cpu_to_be16(from->sb_inopblock);
	memcpy(&to->sb_fname, &from->sb_fname, sizeof(to->sb_fname));
	to->sb_blocklog = from->sb_blocklog;
	to->sb_sectlog = from->sb_sectlog;
	to->sb_inodelog = from->sb_inodelog;
	to->sb_inopblog = from->sb_inopblog;
	to->sb_agblklog = from->sb_agblklog;
	to->sb_rextslog = from->sb_rextslog;
	to->sb_inprogress = from->sb_inprogress;
	to->sb_imax_pct = from->sb_imax_pct;
	to->sb_icount = cpu_to_be64(from->sb_icount);
	to->sb_ifree = cpu_to_be64(from->sb_ifree);
	to->sb_fdblocks = cpu_to_be64(from->sb_fdblocks);
	to->sb_frextents = cpu_to_be64(from->sb_frextents);

	to->sb_flags = from->sb_flags;
	to->sb_shared_vn = from->sb_shared_vn;
	to->sb_inoalignmt = cpu_to_be32(from->sb_inoalignmt);
	to->sb_unit = cpu_to_be32(from->sb_unit);
	to->sb_width = cpu_to_be32(from->sb_width);
	to->sb_dirblklog = from->sb_dirblklog;
	to->sb_logsectlog = from->sb_logsectlog;
	to->sb_logsectsize = cpu_to_be16(from->sb_logsectsize);
	to->sb_logsunit = cpu_to_be32(from->sb_logsunit);

	/*
	 * We need to ensure that bad_features2 always matches features2.
	 * Hence we enforce that here rather than having to remember to do it
	 * everywhere else that updates features2.
	 */
	from->sb_bad_features2 = from->sb_features2;
	to->sb_features2 = cpu_to_be32(from->sb_features2);
	to->sb_bad_features2 = cpu_to_be32(from->sb_bad_features2);

	if (xfs_sb_version_hascrc(from)) {
		to->sb_features_compat = cpu_to_be32(from->sb_features_compat);
		to->sb_features_ro_compat =
				cpu_to_be32(from->sb_features_ro_compat);
		to->sb_features_incompat =
				cpu_to_be32(from->sb_features_incompat);
		to->sb_features_log_incompat =
				cpu_to_be32(from->sb_features_log_incompat);
		to->sb_spino_align = cpu_to_be32(from->sb_spino_align);
		to->sb_lsn = cpu_to_be64(from->sb_lsn);
		if (xfs_sb_version_hasmetauuid(from))
			uuid_copy(&to->sb_meta_uuid, &from->sb_meta_uuid);
	}
}