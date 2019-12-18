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
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;
struct xfs_inode {TYPE_1__* d_ops; struct xfs_mount* i_mount; } ;
struct xfs_da_node_entry {int /*<<< orphan*/  before; int /*<<< orphan*/  hashval; } ;
struct xfs_da_intnode {int /*<<< orphan*/  blkno; } ;
struct xfs_da_args {TYPE_2__* geo; int /*<<< orphan*/  trans; struct xfs_inode* dp; } ;
struct xfs_da3_icnode_hdr {int count; } ;
struct xfs_da3_blkinfo {int /*<<< orphan*/  blkno; } ;
struct xfs_buf {struct xfs_da_intnode* b_addr; int /*<<< orphan*/  b_bn; int /*<<< orphan*/  b_ops; } ;
struct xfs_attr_leafblock {int /*<<< orphan*/  blkno; } ;
struct xfs_attr_leaf_entry {int /*<<< orphan*/  hashval; } ;
struct xfs_attr3_icleaf_hdr {int count; } ;
struct TYPE_4__ {scalar_t__ blksize; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* node_hdr_to_disk ) (struct xfs_da_intnode*,struct xfs_da3_icnode_hdr*) ;struct xfs_da_node_entry* (* node_tree_p ) (struct xfs_da_intnode*) ;int /*<<< orphan*/  (* node_hdr_from_disk ) (struct xfs_da3_icnode_hdr*,struct xfs_da_intnode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_BLFT_ATTR_LEAF_BUF ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct xfs_da_intnode*,struct xfs_da_intnode*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct xfs_da3_icnode_hdr*,struct xfs_da_intnode*) ; 
 struct xfs_da_node_entry* stub2 (struct xfs_da_intnode*) ; 
 int /*<<< orphan*/  stub3 (struct xfs_da_intnode*,struct xfs_da3_icnode_hdr*) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_to_node (struct xfs_da_args*) ; 
 struct xfs_attr_leaf_entry* xfs_attr3_leaf_entryp (struct xfs_da_intnode*) ; 
 int /*<<< orphan*/  xfs_attr3_leaf_hdr_from_disk (TYPE_2__*,struct xfs_attr3_icleaf_hdr*,struct xfs_da_intnode*) ; 
 int xfs_attr3_leaf_read (int /*<<< orphan*/ ,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**) ; 
 int xfs_da3_node_create (struct xfs_da_args*,int /*<<< orphan*/ ,int,struct xfs_buf**,int /*<<< orphan*/ ) ; 
 int xfs_da_get_buf (int /*<<< orphan*/ ,struct xfs_inode*,int /*<<< orphan*/ ,int,struct xfs_buf**,int /*<<< orphan*/ ) ; 
 int xfs_da_grow_inode (struct xfs_da_args*,int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_sb_version_hascrc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 

int
xfs_attr3_leaf_to_node(
	struct xfs_da_args	*args)
{
	struct xfs_attr_leafblock *leaf;
	struct xfs_attr3_icleaf_hdr icleafhdr;
	struct xfs_attr_leaf_entry *entries;
	struct xfs_da_node_entry *btree;
	struct xfs_da3_icnode_hdr icnodehdr;
	struct xfs_da_intnode	*node;
	struct xfs_inode	*dp = args->dp;
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_buf		*bp1 = NULL;
	struct xfs_buf		*bp2 = NULL;
	xfs_dablk_t		blkno;
	int			error;

	trace_xfs_attr_leaf_to_node(args);

	error = xfs_da_grow_inode(args, &blkno);
	if (error)
		goto out;
	error = xfs_attr3_leaf_read(args->trans, dp, 0, -1, &bp1);
	if (error)
		goto out;

	error = xfs_da_get_buf(args->trans, dp, blkno, -1, &bp2, XFS_ATTR_FORK);
	if (error)
		goto out;

	/* copy leaf to new buffer, update identifiers */
	xfs_trans_buf_set_type(args->trans, bp2, XFS_BLFT_ATTR_LEAF_BUF);
	bp2->b_ops = bp1->b_ops;
	memcpy(bp2->b_addr, bp1->b_addr, args->geo->blksize);
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		struct xfs_da3_blkinfo *hdr3 = bp2->b_addr;
		hdr3->blkno = cpu_to_be64(bp2->b_bn);
	}
	xfs_trans_log_buf(args->trans, bp2, 0, args->geo->blksize - 1);

	/*
	 * Set up the new root node.
	 */
	error = xfs_da3_node_create(args, 0, 1, &bp1, XFS_ATTR_FORK);
	if (error)
		goto out;
	node = bp1->b_addr;
	dp->d_ops->node_hdr_from_disk(&icnodehdr, node);
	btree = dp->d_ops->node_tree_p(node);

	leaf = bp2->b_addr;
	xfs_attr3_leaf_hdr_from_disk(args->geo, &icleafhdr, leaf);
	entries = xfs_attr3_leaf_entryp(leaf);

	/* both on-disk, don't endian-flip twice */
	btree[0].hashval = entries[icleafhdr.count - 1].hashval;
	btree[0].before = cpu_to_be32(blkno);
	icnodehdr.count = 1;
	dp->d_ops->node_hdr_to_disk(node, &icnodehdr);
	xfs_trans_log_buf(args->trans, bp1, 0, args->geo->blksize - 1);
	error = 0;
out:
	return error;
}