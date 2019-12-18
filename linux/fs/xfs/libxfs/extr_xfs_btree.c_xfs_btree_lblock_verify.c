#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xfs_failaddr_t ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {struct xfs_mount* b_mount; } ;
struct TYPE_3__ {scalar_t__ bb_leftsib; scalar_t__ bb_rightsib; } ;
struct TYPE_4__ {TYPE_1__ l; } ;
struct xfs_btree_block {TYPE_2__ bb_u; int /*<<< orphan*/  bb_numrecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLFSBLOCK ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (struct xfs_buf*) ; 
 int /*<<< orphan*/ * __this_address ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_verify_fsbno (struct xfs_mount*,int /*<<< orphan*/ ) ; 

xfs_failaddr_t
xfs_btree_lblock_verify(
	struct xfs_buf		*bp,
	unsigned int		max_recs)
{
	struct xfs_mount	*mp = bp->b_mount;
	struct xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	/* numrecs verification */
	if (be16_to_cpu(block->bb_numrecs) > max_recs)
		return __this_address;

	/* sibling pointer verification */
	if (block->bb_u.l.bb_leftsib != cpu_to_be64(NULLFSBLOCK) &&
	    !xfs_verify_fsbno(mp, be64_to_cpu(block->bb_u.l.bb_leftsib)))
		return __this_address;
	if (block->bb_u.l.bb_rightsib != cpu_to_be64(NULLFSBLOCK) &&
	    !xfs_verify_fsbno(mp, be64_to_cpu(block->bb_u.l.bb_rightsib)))
		return __this_address;

	return NULL;
}