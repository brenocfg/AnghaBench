#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bb_numrecs; int /*<<< orphan*/  bb_level; } ;
typedef  TYPE_1__ xfs_bmdr_block_t ;
typedef  int /*<<< orphan*/  xfs_bmbt_key_t ;
struct xfs_mount {int dummy; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
struct xfs_btree_block {int /*<<< orphan*/  bb_numrecs; int /*<<< orphan*/  bb_level; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * XFS_BMAP_BROOT_PTR_ADDR (struct xfs_mount*,struct xfs_btree_block*,int,int) ; 
 int /*<<< orphan*/ * XFS_BMBT_KEY_ADDR (struct xfs_mount*,struct xfs_btree_block*,int) ; 
 int /*<<< orphan*/ * XFS_BMDR_KEY_ADDR (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * XFS_BMDR_PTR_ADDR (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  XFS_BTNUM_BMAP ; 
 int /*<<< orphan*/  XFS_BTREE_LONG_PTRS ; 
 int /*<<< orphan*/  XFS_BUF_DADDR_NULL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xfs_bmdr_maxrecs (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_btree_init_block_int (struct xfs_mount*,struct xfs_btree_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_bmdr_to_bmbt(
	struct xfs_inode	*ip,
	xfs_bmdr_block_t	*dblock,
	int			dblocklen,
	struct xfs_btree_block	*rblock,
	int			rblocklen)
{
	struct xfs_mount	*mp = ip->i_mount;
	int			dmxr;
	xfs_bmbt_key_t		*fkp;
	__be64			*fpp;
	xfs_bmbt_key_t		*tkp;
	__be64			*tpp;

	xfs_btree_init_block_int(mp, rblock, XFS_BUF_DADDR_NULL,
				 XFS_BTNUM_BMAP, 0, 0, ip->i_ino,
				 XFS_BTREE_LONG_PTRS);
	rblock->bb_level = dblock->bb_level;
	ASSERT(be16_to_cpu(rblock->bb_level) > 0);
	rblock->bb_numrecs = dblock->bb_numrecs;
	dmxr = xfs_bmdr_maxrecs(dblocklen, 0);
	fkp = XFS_BMDR_KEY_ADDR(dblock, 1);
	tkp = XFS_BMBT_KEY_ADDR(mp, rblock, 1);
	fpp = XFS_BMDR_PTR_ADDR(dblock, 1, dmxr);
	tpp = XFS_BMAP_BROOT_PTR_ADDR(mp, rblock, 1, rblocklen);
	dmxr = be16_to_cpu(dblock->bb_numrecs);
	memcpy(tkp, fkp, sizeof(*fkp) * dmxr);
	memcpy(tpp, fpp, sizeof(*fpp) * dmxr);
}