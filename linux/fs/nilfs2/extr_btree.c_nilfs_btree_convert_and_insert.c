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
typedef  union nilfs_bmap_ptr_req {int dummy; } nilfs_bmap_ptr_req ;
struct nilfs_bmap_stats {int /*<<< orphan*/  bs_nblocks; } ;
struct nilfs_bmap {int /*<<< orphan*/  b_inode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int NILFS_BTREE_NODE_NCHILDREN_MAX (int /*<<< orphan*/ ) ; 
 int NILFS_BTREE_ROOT_NCHILDREN_MAX ; 
 int /*<<< orphan*/  nilfs_btree_commit_convert_and_insert (struct nilfs_bmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,union nilfs_bmap_ptr_req*,union nilfs_bmap_ptr_req*,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_btree_node_size (struct nilfs_bmap*) ; 
 int nilfs_btree_prepare_convert_and_insert (struct nilfs_bmap*,int /*<<< orphan*/ ,union nilfs_bmap_ptr_req*,union nilfs_bmap_ptr_req*,struct buffer_head**,struct nilfs_bmap_stats*) ; 
 int /*<<< orphan*/  nilfs_inode_add_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nilfs_btree_convert_and_insert(struct nilfs_bmap *btree,
				   __u64 key, __u64 ptr,
				   const __u64 *keys, const __u64 *ptrs, int n)
{
	struct buffer_head *bh = NULL;
	union nilfs_bmap_ptr_req dreq, nreq, *di, *ni;
	struct nilfs_bmap_stats stats;
	int ret;

	if (n + 1 <= NILFS_BTREE_ROOT_NCHILDREN_MAX) {
		di = &dreq;
		ni = NULL;
	} else if ((n + 1) <= NILFS_BTREE_NODE_NCHILDREN_MAX(
			   nilfs_btree_node_size(btree))) {
		di = &dreq;
		ni = &nreq;
	} else {
		di = NULL;
		ni = NULL;
		BUG();
	}

	ret = nilfs_btree_prepare_convert_and_insert(btree, key, di, ni, &bh,
						     &stats);
	if (ret < 0)
		return ret;
	nilfs_btree_commit_convert_and_insert(btree, key, ptr, keys, ptrs, n,
					      di, ni, bh);
	nilfs_inode_add_blocks(btree->b_inode, stats.bs_nblocks);
	return 0;
}