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
struct xfs_sb {int /*<<< orphan*/  sb_logsunit; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_logsectsize; int /*<<< orphan*/  sb_width; int /*<<< orphan*/  sb_unit; int /*<<< orphan*/  sb_uuid; int /*<<< orphan*/  sb_logstart; int /*<<< orphan*/  sb_rextents; int /*<<< orphan*/  sb_rblocks; int /*<<< orphan*/  sb_dblocks; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_inodesize; int /*<<< orphan*/  sb_sectsize; int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_agcount; int /*<<< orphan*/  sb_agblocks; int /*<<< orphan*/  sb_rextsize; } ;
struct xfs_fsop_geom {int flags; int /*<<< orphan*/  version; int /*<<< orphan*/  logsunit; int /*<<< orphan*/  dirblocksize; int /*<<< orphan*/  rtsectsize; int /*<<< orphan*/  logsectsize; int /*<<< orphan*/  swidth; int /*<<< orphan*/  sunit; int /*<<< orphan*/  uuid; int /*<<< orphan*/  logstart; int /*<<< orphan*/  rtextents; int /*<<< orphan*/  rtblocks; int /*<<< orphan*/  datablocks; int /*<<< orphan*/  imaxpct; int /*<<< orphan*/  inodesize; int /*<<< orphan*/  sectsize; int /*<<< orphan*/  logblocks; int /*<<< orphan*/  agcount; int /*<<< orphan*/  agblocks; int /*<<< orphan*/  rtextsize; int /*<<< orphan*/  blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBSIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int XFS_FSOP_GEOM_FLAGS_ATTR ; 
 int XFS_FSOP_GEOM_FLAGS_ATTR2 ; 
 int XFS_FSOP_GEOM_FLAGS_DALIGN ; 
 int XFS_FSOP_GEOM_FLAGS_DIRV2 ; 
 int XFS_FSOP_GEOM_FLAGS_DIRV2CI ; 
 int XFS_FSOP_GEOM_FLAGS_EXTFLG ; 
 int XFS_FSOP_GEOM_FLAGS_FINOBT ; 
 int XFS_FSOP_GEOM_FLAGS_FTYPE ; 
 int XFS_FSOP_GEOM_FLAGS_IALIGN ; 
 int XFS_FSOP_GEOM_FLAGS_LAZYSB ; 
 int XFS_FSOP_GEOM_FLAGS_LOGV2 ; 
 int XFS_FSOP_GEOM_FLAGS_NLINK ; 
 int XFS_FSOP_GEOM_FLAGS_PROJID32 ; 
 int XFS_FSOP_GEOM_FLAGS_QUOTA ; 
 int XFS_FSOP_GEOM_FLAGS_REFLINK ; 
 int XFS_FSOP_GEOM_FLAGS_RMAPBT ; 
 int XFS_FSOP_GEOM_FLAGS_SECTOR ; 
 int XFS_FSOP_GEOM_FLAGS_SPINODES ; 
 int XFS_FSOP_GEOM_FLAGS_V5SB ; 
 int /*<<< orphan*/  XFS_FSOP_GEOM_VERSION ; 
 int /*<<< orphan*/  XFS_FSOP_GEOM_VERSION_V5 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct xfs_fsop_geom*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_dir2_dirblock_bytes (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasalign (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasasciici (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasattr (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasattr2 (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hascrc (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasdalign (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasfinobt (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasftype (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_haslazysbcount (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_haslogv2 (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasprojid32bit (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasquota (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasreflink (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hasrmapbt (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hassector (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hassparseinodes (struct xfs_sb*) ; 

void
xfs_fs_geometry(
	struct xfs_sb		*sbp,
	struct xfs_fsop_geom	*geo,
	int			struct_version)
{
	memset(geo, 0, sizeof(struct xfs_fsop_geom));

	geo->blocksize = sbp->sb_blocksize;
	geo->rtextsize = sbp->sb_rextsize;
	geo->agblocks = sbp->sb_agblocks;
	geo->agcount = sbp->sb_agcount;
	geo->logblocks = sbp->sb_logblocks;
	geo->sectsize = sbp->sb_sectsize;
	geo->inodesize = sbp->sb_inodesize;
	geo->imaxpct = sbp->sb_imax_pct;
	geo->datablocks = sbp->sb_dblocks;
	geo->rtblocks = sbp->sb_rblocks;
	geo->rtextents = sbp->sb_rextents;
	geo->logstart = sbp->sb_logstart;
	BUILD_BUG_ON(sizeof(geo->uuid) != sizeof(sbp->sb_uuid));
	memcpy(geo->uuid, &sbp->sb_uuid, sizeof(sbp->sb_uuid));

	if (struct_version < 2)
		return;

	geo->sunit = sbp->sb_unit;
	geo->swidth = sbp->sb_width;

	if (struct_version < 3)
		return;

	geo->version = XFS_FSOP_GEOM_VERSION;
	geo->flags = XFS_FSOP_GEOM_FLAGS_NLINK |
		     XFS_FSOP_GEOM_FLAGS_DIRV2 |
		     XFS_FSOP_GEOM_FLAGS_EXTFLG;
	if (xfs_sb_version_hasattr(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_ATTR;
	if (xfs_sb_version_hasquota(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_QUOTA;
	if (xfs_sb_version_hasalign(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_IALIGN;
	if (xfs_sb_version_hasdalign(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_DALIGN;
	if (xfs_sb_version_hassector(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_SECTOR;
	if (xfs_sb_version_hasasciici(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_DIRV2CI;
	if (xfs_sb_version_haslazysbcount(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_LAZYSB;
	if (xfs_sb_version_hasattr2(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_ATTR2;
	if (xfs_sb_version_hasprojid32bit(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_PROJID32;
	if (xfs_sb_version_hascrc(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_V5SB;
	if (xfs_sb_version_hasftype(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_FTYPE;
	if (xfs_sb_version_hasfinobt(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_FINOBT;
	if (xfs_sb_version_hassparseinodes(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_SPINODES;
	if (xfs_sb_version_hasrmapbt(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_RMAPBT;
	if (xfs_sb_version_hasreflink(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_REFLINK;
	if (xfs_sb_version_hassector(sbp))
		geo->logsectsize = sbp->sb_logsectsize;
	else
		geo->logsectsize = BBSIZE;
	geo->rtsectsize = sbp->sb_blocksize;
	geo->dirblocksize = xfs_dir2_dirblock_bytes(sbp);

	if (struct_version < 4)
		return;

	if (xfs_sb_version_haslogv2(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_LOGV2;

	geo->logsunit = sbp->sb_logsunit;

	if (struct_version < 5)
		return;

	geo->version = XFS_FSOP_GEOM_VERSION_V5;
}