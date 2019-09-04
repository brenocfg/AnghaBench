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
struct nilfs_btree_readahead_info {int ncmax; int index; int max_ra_blocks; struct nilfs_btree_node* node; } ;
struct nilfs_btree_path {int bp_index; int /*<<< orphan*/ * bp_bh; } ;
struct nilfs_btree_node {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NILFS_BMAP_USE_VBN (struct nilfs_bmap const*) ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 int __nilfs_btree_get_block (struct nilfs_bmap const*,scalar_t__,int /*<<< orphan*/ **,struct nilfs_btree_readahead_info*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap const*) ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap const*,struct nilfs_btree_path*,scalar_t__,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 
 void* nilfs_btree_get_node (struct nilfs_bmap const*,struct nilfs_btree_path*,int,int*) ; 
 struct nilfs_btree_node* nilfs_btree_get_nonroot_node (struct nilfs_btree_path*,int) ; 
 int nilfs_btree_height (struct nilfs_bmap const*) ; 
 int nilfs_btree_nchildren_per_block (struct nilfs_bmap const*) ; 
 scalar_t__ nilfs_btree_node_get_key (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 scalar_t__ nilfs_btree_node_get_ptr (struct nilfs_btree_node*,int,int) ; 
 int nilfs_dat_translate (struct inode*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int nilfs_btree_lookup_contig(const struct nilfs_bmap *btree,
				     __u64 key, __u64 *ptrp,
				     unsigned int maxblocks)
{
	struct nilfs_btree_path *path;
	struct nilfs_btree_node *node;
	struct inode *dat = NULL;
	__u64 ptr, ptr2;
	sector_t blocknr;
	int level = NILFS_BTREE_LEVEL_NODE_MIN;
	int ret, cnt, index, maxlevel, ncmax;
	struct nilfs_btree_readahead_info p;

	path = nilfs_btree_alloc_path();
	if (path == NULL)
		return -ENOMEM;

	ret = nilfs_btree_do_lookup(btree, path, key, &ptr, level, 1);
	if (ret < 0)
		goto out;

	if (NILFS_BMAP_USE_VBN(btree)) {
		dat = nilfs_bmap_get_dat(btree);
		ret = nilfs_dat_translate(dat, ptr, &blocknr);
		if (ret < 0)
			goto out;
		ptr = blocknr;
	}
	cnt = 1;
	if (cnt == maxblocks)
		goto end;

	maxlevel = nilfs_btree_height(btree) - 1;
	node = nilfs_btree_get_node(btree, path, level, &ncmax);
	index = path[level].bp_index + 1;
	for (;;) {
		while (index < nilfs_btree_node_get_nchildren(node)) {
			if (nilfs_btree_node_get_key(node, index) !=
			    key + cnt)
				goto end;
			ptr2 = nilfs_btree_node_get_ptr(node, index, ncmax);
			if (dat) {
				ret = nilfs_dat_translate(dat, ptr2, &blocknr);
				if (ret < 0)
					goto out;
				ptr2 = blocknr;
			}
			if (ptr2 != ptr + cnt || ++cnt == maxblocks)
				goto end;
			index++;
			continue;
		}
		if (level == maxlevel)
			break;

		/* look-up right sibling node */
		p.node = nilfs_btree_get_node(btree, path, level + 1, &p.ncmax);
		p.index = path[level + 1].bp_index + 1;
		p.max_ra_blocks = 7;
		if (p.index >= nilfs_btree_node_get_nchildren(p.node) ||
		    nilfs_btree_node_get_key(p.node, p.index) != key + cnt)
			break;
		ptr2 = nilfs_btree_node_get_ptr(p.node, p.index, p.ncmax);
		path[level + 1].bp_index = p.index;

		brelse(path[level].bp_bh);
		path[level].bp_bh = NULL;

		ret = __nilfs_btree_get_block(btree, ptr2, &path[level].bp_bh,
					      &p);
		if (ret < 0)
			goto out;
		node = nilfs_btree_get_nonroot_node(path, level);
		ncmax = nilfs_btree_nchildren_per_block(btree);
		index = 0;
		path[level].bp_index = index;
	}
 end:
	*ptrp = ptr;
	ret = cnt;
 out:
	nilfs_btree_free_path(path);
	return ret;
}