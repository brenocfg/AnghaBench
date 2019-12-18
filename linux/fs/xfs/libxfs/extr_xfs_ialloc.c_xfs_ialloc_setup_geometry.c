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
typedef  int uint64_t ;
typedef  long long uint ;
struct xfs_sb {int sb_inopblog; int sb_blocksize; int sb_spino_align; int sb_imax_pct; int sb_dblocks; int sb_inodesize; scalar_t__ sb_inoalignmt; int /*<<< orphan*/  sb_inopblock; scalar_t__ sb_agblklog; } ;
struct xfs_mount {int m_dalign; struct xfs_sb m_sb; } ;
struct xfs_ino_geometry {int* inobt_mxr; int* inobt_mnr; int ialloc_inos; int ialloc_blks; int ialloc_min_blks; int inode_cluster_size_raw; int blocks_per_cluster; int cluster_align; int inoalign_mask; int ialloc_align; void* cluster_align_inodes; void* inodes_per_cluster; int /*<<< orphan*/  inode_cluster_size; void* maxicount; int /*<<< orphan*/  inobt_maxlevels; scalar_t__ agino_log; } ;

/* Variables and functions */
 struct xfs_ino_geometry* M_IGEO (struct xfs_mount*) ; 
 scalar_t__ XFS_B_TO_FSBT (struct xfs_mount*,int) ; 
 int XFS_DINODE_MIN_SIZE ; 
 int /*<<< orphan*/  XFS_FSB_TO_B (struct xfs_mount*,int) ; 
 void* XFS_FSB_TO_INO (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_INODES_PER_CHUNK ; 
 long long XFS_INODES_PER_CHUNK_LOG ; 
 int XFS_INODE_BIG_CLUSTER_SIZE ; 
 long long XFS_INO_AGINO_BITS (struct xfs_mount*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint16_t ; 
 int /*<<< orphan*/  xfs_btree_compute_maxlevels (int*,long long) ; 
 void* xfs_inobt_maxrecs (struct xfs_mount*,int,int) ; 
 scalar_t__ xfs_sb_version_hasalign (struct xfs_sb*) ; 
 scalar_t__ xfs_sb_version_hascrc (struct xfs_sb*) ; 

void
xfs_ialloc_setup_geometry(
	struct xfs_mount	*mp)
{
	struct xfs_sb		*sbp = &mp->m_sb;
	struct xfs_ino_geometry	*igeo = M_IGEO(mp);
	uint64_t		icount;
	uint			inodes;

	/* Compute inode btree geometry. */
	igeo->agino_log = sbp->sb_inopblog + sbp->sb_agblklog;
	igeo->inobt_mxr[0] = xfs_inobt_maxrecs(mp, sbp->sb_blocksize, 1);
	igeo->inobt_mxr[1] = xfs_inobt_maxrecs(mp, sbp->sb_blocksize, 0);
	igeo->inobt_mnr[0] = igeo->inobt_mxr[0] / 2;
	igeo->inobt_mnr[1] = igeo->inobt_mxr[1] / 2;

	igeo->ialloc_inos = max_t(uint16_t, XFS_INODES_PER_CHUNK,
			sbp->sb_inopblock);
	igeo->ialloc_blks = igeo->ialloc_inos >> sbp->sb_inopblog;

	if (sbp->sb_spino_align)
		igeo->ialloc_min_blks = sbp->sb_spino_align;
	else
		igeo->ialloc_min_blks = igeo->ialloc_blks;

	/* Compute and fill in value of m_ino_geo.inobt_maxlevels. */
	inodes = (1LL << XFS_INO_AGINO_BITS(mp)) >> XFS_INODES_PER_CHUNK_LOG;
	igeo->inobt_maxlevels = xfs_btree_compute_maxlevels(igeo->inobt_mnr,
			inodes);

	/*
	 * Set the maximum inode count for this filesystem, being careful not
	 * to use obviously garbage sb_inopblog/sb_inopblock values.  Regular
	 * users should never get here due to failing sb verification, but
	 * certain users (xfs_db) need to be usable even with corrupt metadata.
	 */
	if (sbp->sb_imax_pct && igeo->ialloc_blks) {
		/*
		 * Make sure the maximum inode count is a multiple
		 * of the units we allocate inodes in.
		 */
		icount = sbp->sb_dblocks * sbp->sb_imax_pct;
		do_div(icount, 100);
		do_div(icount, igeo->ialloc_blks);
		igeo->maxicount = XFS_FSB_TO_INO(mp,
				icount * igeo->ialloc_blks);
	} else {
		igeo->maxicount = 0;
	}

	/*
	 * Compute the desired size of an inode cluster buffer size, which
	 * starts at 8K and (on v5 filesystems) scales up with larger inode
	 * sizes.
	 *
	 * Preserve the desired inode cluster size because the sparse inodes
	 * feature uses that desired size (not the actual size) to compute the
	 * sparse inode alignment.  The mount code validates this value, so we
	 * cannot change the behavior.
	 */
	igeo->inode_cluster_size_raw = XFS_INODE_BIG_CLUSTER_SIZE;
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		int	new_size = igeo->inode_cluster_size_raw;

		new_size *= mp->m_sb.sb_inodesize / XFS_DINODE_MIN_SIZE;
		if (mp->m_sb.sb_inoalignmt >= XFS_B_TO_FSBT(mp, new_size))
			igeo->inode_cluster_size_raw = new_size;
	}

	/* Calculate inode cluster ratios. */
	if (igeo->inode_cluster_size_raw > mp->m_sb.sb_blocksize)
		igeo->blocks_per_cluster = XFS_B_TO_FSBT(mp,
				igeo->inode_cluster_size_raw);
	else
		igeo->blocks_per_cluster = 1;
	igeo->inode_cluster_size = XFS_FSB_TO_B(mp, igeo->blocks_per_cluster);
	igeo->inodes_per_cluster = XFS_FSB_TO_INO(mp, igeo->blocks_per_cluster);

	/* Calculate inode cluster alignment. */
	if (xfs_sb_version_hasalign(&mp->m_sb) &&
	    mp->m_sb.sb_inoalignmt >= igeo->blocks_per_cluster)
		igeo->cluster_align = mp->m_sb.sb_inoalignmt;
	else
		igeo->cluster_align = 1;
	igeo->inoalign_mask = igeo->cluster_align - 1;
	igeo->cluster_align_inodes = XFS_FSB_TO_INO(mp, igeo->cluster_align);

	/*
	 * If we are using stripe alignment, check whether
	 * the stripe unit is a multiple of the inode alignment
	 */
	if (mp->m_dalign && igeo->inoalign_mask &&
	    !(mp->m_dalign & igeo->inoalign_mask))
		igeo->ialloc_align = mp->m_dalign;
	else
		igeo->ialloc_align = 0;
}