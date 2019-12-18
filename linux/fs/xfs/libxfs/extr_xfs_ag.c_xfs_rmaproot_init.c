#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfs_rmap_rec {scalar_t__ rm_offset; void* rm_owner; void* rm_blockcount; void* rm_startblock; } ;
struct TYPE_2__ {int sb_logblocks; int /*<<< orphan*/  sb_logstart; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_block {int /*<<< orphan*/  bb_numrecs; } ;
struct aghdr_init_data {int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 int XFS_BNO_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_BTNUM_RMAP ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 int XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_IBT_BLOCK (struct xfs_mount*) ; 
 int XFS_RMAP_BLOCK (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_AG ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_FS ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_INOBT ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_LOG ; 
 int /*<<< orphan*/  XFS_RMAP_OWN_REFC ; 
 struct xfs_rmap_rec* XFS_RMAP_REC_ADDR (struct xfs_btree_block*,int) ; 
 int /*<<< orphan*/  be16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_log_ag (struct xfs_mount*,struct aghdr_init_data*) ; 
 int /*<<< orphan*/  xfs_btree_init_block (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfs_refc_block (struct xfs_mount*) ; 
 scalar_t__ xfs_sb_version_hasreflink (TYPE_1__*) ; 

__attribute__((used)) static void
xfs_rmaproot_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	struct xfs_rmap_rec	*rrec;

	xfs_btree_init_block(mp, bp, XFS_BTNUM_RMAP, 0, 4, id->agno);

	/*
	 * mark the AG header regions as static metadata The BNO
	 * btree block is the first block after the headers, so
	 * it's location defines the size of region the static
	 * metadata consumes.
	 *
	 * Note: unlike mkfs, we never have to account for log
	 * space when growing the data regions
	 */
	rrec = XFS_RMAP_REC_ADDR(block, 1);
	rrec->rm_startblock = 0;
	rrec->rm_blockcount = cpu_to_be32(XFS_BNO_BLOCK(mp));
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_FS);
	rrec->rm_offset = 0;

	/* account freespace btree root blocks */
	rrec = XFS_RMAP_REC_ADDR(block, 2);
	rrec->rm_startblock = cpu_to_be32(XFS_BNO_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(2);
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_AG);
	rrec->rm_offset = 0;

	/* account inode btree root blocks */
	rrec = XFS_RMAP_REC_ADDR(block, 3);
	rrec->rm_startblock = cpu_to_be32(XFS_IBT_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(XFS_RMAP_BLOCK(mp) -
					  XFS_IBT_BLOCK(mp));
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_INOBT);
	rrec->rm_offset = 0;

	/* account for rmap btree root */
	rrec = XFS_RMAP_REC_ADDR(block, 4);
	rrec->rm_startblock = cpu_to_be32(XFS_RMAP_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(1);
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_AG);
	rrec->rm_offset = 0;

	/* account for refc btree root */
	if (xfs_sb_version_hasreflink(&mp->m_sb)) {
		rrec = XFS_RMAP_REC_ADDR(block, 5);
		rrec->rm_startblock = cpu_to_be32(xfs_refc_block(mp));
		rrec->rm_blockcount = cpu_to_be32(1);
		rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_REFC);
		rrec->rm_offset = 0;
		be16_add_cpu(&block->bb_numrecs, 1);
	}

	/* account for the log space */
	if (is_log_ag(mp, id)) {
		rrec = XFS_RMAP_REC_ADDR(block,
				be16_to_cpu(block->bb_numrecs) + 1);
		rrec->rm_startblock = cpu_to_be32(
				XFS_FSB_TO_AGBNO(mp, mp->m_sb.sb_logstart));
		rrec->rm_blockcount = cpu_to_be32(mp->m_sb.sb_logblocks);
		rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_LOG);
		rrec->rm_offset = 0;
		be16_add_cpu(&block->bb_numrecs, 1);
	}
}