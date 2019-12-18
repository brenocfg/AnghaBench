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
typedef  scalar_t__ xfs_agblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  sb_logblocks; int /*<<< orphan*/  sb_logstart; } ;
struct xfs_mount {scalar_t__ m_ag_prealloc_blocks; TYPE_1__ m_sb; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_block {scalar_t__ bb_numrecs; } ;
struct xfs_alloc_rec {void* ar_blockcount; void* ar_startblock; } ;
struct aghdr_init_data {scalar_t__ agsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct xfs_alloc_rec* XFS_ALLOC_REC_ADDR (struct xfs_mount*,struct xfs_btree_block*,int) ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 scalar_t__ XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ is_log_ag (struct xfs_mount*,struct aghdr_init_data*) ; 

__attribute__((used)) static void
xfs_freesp_init_recs(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_alloc_rec	*arec;
	struct xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	arec = XFS_ALLOC_REC_ADDR(mp, XFS_BUF_TO_BLOCK(bp), 1);
	arec->ar_startblock = cpu_to_be32(mp->m_ag_prealloc_blocks);

	if (is_log_ag(mp, id)) {
		struct xfs_alloc_rec	*nrec;
		xfs_agblock_t		start = XFS_FSB_TO_AGBNO(mp,
							mp->m_sb.sb_logstart);

		ASSERT(start >= mp->m_ag_prealloc_blocks);
		if (start != mp->m_ag_prealloc_blocks) {
			/*
			 * Modify first record to pad stripe align of log
			 */
			arec->ar_blockcount = cpu_to_be32(start -
						mp->m_ag_prealloc_blocks);
			nrec = arec + 1;

			/*
			 * Insert second record at start of internal log
			 * which then gets trimmed.
			 */
			nrec->ar_startblock = cpu_to_be32(
					be32_to_cpu(arec->ar_startblock) +
					be32_to_cpu(arec->ar_blockcount));
			arec = nrec;
			be16_add_cpu(&block->bb_numrecs, 1);
		}
		/*
		 * Change record start to after the internal log
		 */
		be32_add_cpu(&arec->ar_startblock, mp->m_sb.sb_logblocks);
	}

	/*
	 * Calculate the record block count and check for the case where
	 * the log might have consumed all available space in the AG. If
	 * so, reset the record count to 0 to avoid exposure of an invalid
	 * record start block.
	 */
	arec->ar_blockcount = cpu_to_be32(id->agsize -
					  be32_to_cpu(arec->ar_startblock));
	if (!arec->ar_blockcount)
		block->bb_numrecs = 0;
}