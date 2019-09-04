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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
struct xfs_da_blkinfo {int /*<<< orphan*/  magic; } ;
struct xfs_buf {TYPE_1__* b_ops; struct xfs_da_blkinfo* b_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* verify_struct ) (struct xfs_buf*) ;} ;

/* Variables and functions */
#define  XFS_ATTR3_LEAF_MAGIC 133 
#define  XFS_ATTR_LEAF_MAGIC 132 
#define  XFS_DA3_NODE_MAGIC 131 
#define  XFS_DA_NODE_MAGIC 130 
#define  XFS_DIR2_LEAFN_MAGIC 129 
#define  XFS_DIR3_LEAFN_MAGIC 128 
 int /*<<< orphan*/  __this_address ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xfs_buf*) ; 
 int /*<<< orphan*/  stub2 (struct xfs_buf*) ; 
 TYPE_1__ xfs_attr3_leaf_buf_ops ; 
 int /*<<< orphan*/  xfs_da3_node_verify (struct xfs_buf*) ; 
 TYPE_1__ xfs_dir3_leafn_buf_ops ; 

__attribute__((used)) static xfs_failaddr_t
xfs_da3_node_verify_struct(
	struct xfs_buf		*bp)
{
	struct xfs_da_blkinfo	*info = bp->b_addr;

	switch (be16_to_cpu(info->magic)) {
	case XFS_DA3_NODE_MAGIC:
	case XFS_DA_NODE_MAGIC:
		return xfs_da3_node_verify(bp);
	case XFS_ATTR_LEAF_MAGIC:
	case XFS_ATTR3_LEAF_MAGIC:
		bp->b_ops = &xfs_attr3_leaf_buf_ops;
		return bp->b_ops->verify_struct(bp);
	case XFS_DIR2_LEAFN_MAGIC:
	case XFS_DIR3_LEAFN_MAGIC:
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		return bp->b_ops->verify_struct(bp);
	default:
		return __this_address;
	}
}