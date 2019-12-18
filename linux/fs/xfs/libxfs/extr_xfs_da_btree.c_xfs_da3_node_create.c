#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct TYPE_6__ {int /*<<< orphan*/  sb_meta_uuid; } ;
struct xfs_mount {TYPE_3__ m_sb; } ;
struct xfs_inode {TYPE_2__* d_ops; int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  uuid; void* owner; void* blkno; } ;
struct xfs_da_intnode {int /*<<< orphan*/  hdr; TYPE_1__ info; } ;
struct xfs_da_args {struct xfs_inode* dp; struct xfs_trans* trans; } ;
struct xfs_da3_node_hdr {int /*<<< orphan*/  hdr; TYPE_1__ info; } ;
struct xfs_da3_icnode_hdr {int level; int /*<<< orphan*/  magic; int /*<<< orphan*/  member_0; } ;
struct xfs_buf {int /*<<< orphan*/  b_bn; struct xfs_da_intnode* b_addr; int /*<<< orphan*/ * b_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  node_hdr_size; int /*<<< orphan*/  (* node_hdr_to_disk ) (struct xfs_da_intnode*,struct xfs_da3_icnode_hdr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_BLFT_DA_NODE_BUF ; 
 int /*<<< orphan*/  XFS_DA3_NODE_MAGIC ; 
 int /*<<< orphan*/  XFS_DA_LOGRANGE (struct xfs_da_intnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DA_NODE_MAGIC ; 
 int XFS_DA_NODE_MAXDEPTH ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xfs_da_intnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct xfs_da_intnode*,struct xfs_da3_icnode_hdr*) ; 
 int /*<<< orphan*/  trace_xfs_da_node_create (struct xfs_da_args*) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_da3_node_buf_ops ; 
 int xfs_da_get_buf (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**,int) ; 
 scalar_t__ xfs_sb_version_hascrc (TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 

int
xfs_da3_node_create(
	struct xfs_da_args	*args,
	xfs_dablk_t		blkno,
	int			level,
	struct xfs_buf		**bpp,
	int			whichfork)
{
	struct xfs_da_intnode	*node;
	struct xfs_trans	*tp = args->trans;
	struct xfs_mount	*mp = tp->t_mountp;
	struct xfs_da3_icnode_hdr ichdr = {0};
	struct xfs_buf		*bp;
	int			error;
	struct xfs_inode	*dp = args->dp;

	trace_xfs_da_node_create(args);
	ASSERT(level <= XFS_DA_NODE_MAXDEPTH);

	error = xfs_da_get_buf(tp, dp, blkno, -1, &bp, whichfork);
	if (error)
		return error;
	bp->b_ops = &xfs_da3_node_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DA_NODE_BUF);
	node = bp->b_addr;

	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_da3_node_hdr *hdr3 = bp->b_addr;

		memset(hdr3, 0, sizeof(struct xfs_da3_node_hdr));
		ichdr.magic = XFS_DA3_NODE_MAGIC;
		hdr3->info.blkno = cpu_to_be64(bp->b_bn);
		hdr3->info.owner = cpu_to_be64(args->dp->i_ino);
		uuid_copy(&hdr3->info.uuid, &mp->m_sb.sb_meta_uuid);
	} else {
		ichdr.magic = XFS_DA_NODE_MAGIC;
	}
	ichdr.level = level;

	dp->d_ops->node_hdr_to_disk(node, &ichdr);
	xfs_trans_log_buf(tp, bp,
		XFS_DA_LOGRANGE(node, &node->hdr, dp->d_ops->node_hdr_size));

	*bpp = bp;
	return 0;
}