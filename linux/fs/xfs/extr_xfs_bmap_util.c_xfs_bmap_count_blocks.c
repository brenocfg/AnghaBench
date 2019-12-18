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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  scalar_t__ xfs_filblks_t ;
typedef  scalar_t__ xfs_extnum_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_agblocks; int /*<<< orphan*/  sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_ifork {int if_flags; int /*<<< orphan*/  if_broot_bytes; struct xfs_btree_block* if_broot; } ;
struct xfs_btree_block {int /*<<< orphan*/  bb_level; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  NULLFSBLOCK ; 
 int /*<<< orphan*/ * XFS_BMAP_BROOT_PTR_ADDR (struct xfs_mount*,struct xfs_btree_block*,int,int /*<<< orphan*/ ) ; 
#define  XFS_DINODE_FMT_BTREE 129 
#define  XFS_DINODE_FMT_EXTENTS 128 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_IFEXTENTS ; 
 int XFS_IFORK_FORMAT (struct xfs_inode*,int) ; 
 struct xfs_ifork* XFS_IFORK_PTR (struct xfs_inode*,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_bmap_count_leaves (struct xfs_ifork*,scalar_t__*) ; 
 int xfs_bmap_count_tree (struct xfs_mount*,struct xfs_trans*,struct xfs_ifork*,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 int xfs_iread_extents (struct xfs_trans*,struct xfs_inode*,int) ; 

int
xfs_bmap_count_blocks(
	struct xfs_trans	*tp,
	struct xfs_inode	*ip,
	int			whichfork,
	xfs_extnum_t		*nextents,
	xfs_filblks_t		*count)
{
	struct xfs_mount	*mp;	/* file system mount structure */
	__be64			*pp;	/* pointer to block address */
	struct xfs_btree_block	*block;	/* current btree block */
	struct xfs_ifork	*ifp;	/* fork structure */
	xfs_fsblock_t		bno;	/* block # of "block" */
	int			level;	/* btree level, for checking */
	int			error;

	bno = NULLFSBLOCK;
	mp = ip->i_mount;
	*nextents = 0;
	*count = 0;
	ifp = XFS_IFORK_PTR(ip, whichfork);
	if (!ifp)
		return 0;

	switch (XFS_IFORK_FORMAT(ip, whichfork)) {
	case XFS_DINODE_FMT_EXTENTS:
		*nextents = xfs_bmap_count_leaves(ifp, count);
		return 0;
	case XFS_DINODE_FMT_BTREE:
		if (!(ifp->if_flags & XFS_IFEXTENTS)) {
			error = xfs_iread_extents(tp, ip, whichfork);
			if (error)
				return error;
		}

		/*
		 * Root level must use BMAP_BROOT_PTR_ADDR macro to get ptr out.
		 */
		block = ifp->if_broot;
		level = be16_to_cpu(block->bb_level);
		ASSERT(level > 0);
		pp = XFS_BMAP_BROOT_PTR_ADDR(mp, block, 1, ifp->if_broot_bytes);
		bno = be64_to_cpu(*pp);
		ASSERT(bno != NULLFSBLOCK);
		ASSERT(XFS_FSB_TO_AGNO(mp, bno) < mp->m_sb.sb_agcount);
		ASSERT(XFS_FSB_TO_AGBNO(mp, bno) < mp->m_sb.sb_agblocks);

		error = xfs_bmap_count_tree(mp, tp, ifp, bno, level,
				nextents, count);
		if (error) {
			XFS_ERROR_REPORT("xfs_bmap_count_blocks(2)",
					XFS_ERRLEVEL_LOW, mp);
			return -EFSCORRUPTED;
		}
		return 0;
	}

	return 0;
}