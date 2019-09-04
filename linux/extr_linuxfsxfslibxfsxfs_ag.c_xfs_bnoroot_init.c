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
struct xfs_mount {scalar_t__ m_ag_prealloc_blocks; } ;
struct xfs_buf {int dummy; } ;
struct xfs_alloc_rec {void* ar_startblock; void* ar_blockcount; } ;
struct aghdr_init_data {scalar_t__ agsize; int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 struct xfs_alloc_rec* XFS_ALLOC_REC_ADDR (struct xfs_mount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XFS_BTNUM_BNO ; 
 int /*<<< orphan*/  XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  xfs_btree_init_block (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_bnoroot_init(
	struct xfs_mount	*mp,
	struct xfs_buf		*bp,
	struct aghdr_init_data	*id)
{
	struct xfs_alloc_rec	*arec;

	xfs_btree_init_block(mp, bp, XFS_BTNUM_BNO, 0, 1, id->agno, 0);
	arec = XFS_ALLOC_REC_ADDR(mp, XFS_BUF_TO_BLOCK(bp), 1);
	arec->ar_startblock = cpu_to_be32(mp->m_ag_prealloc_blocks);
	arec->ar_blockcount = cpu_to_be32(id->agsize -
					  be32_to_cpu(arec->ar_startblock));
}