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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_node {int dummy; } ;
struct dnode_of_data {int ofs_in_node; int /*<<< orphan*/  nid; int /*<<< orphan*/  inode; int /*<<< orphan*/  node_page; scalar_t__ data_blkaddr; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ block_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 
 struct f2fs_node* F2FS_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FI_FIRST_BLOCK_WRITTEN ; 
 scalar_t__ IS_INODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  REQ_TIME ; 
 scalar_t__ __is_valid_data_blkaddr (scalar_t__) ; 
 int /*<<< orphan*/ * blkaddr_in_node (struct f2fs_node*) ; 
 int /*<<< orphan*/  clear_inode_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_valid_block_count (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ f2fs_has_extra_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_invalidate_blocks (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_set_data_blkaddr (struct dnode_of_data*) ; 
 scalar_t__ f2fs_start_bidx_of_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_extent_cache_range (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_update_time (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int get_extra_isize (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofs_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_truncate_data_blocks_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void f2fs_truncate_data_blocks_range(struct dnode_of_data *dn, int count)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	struct f2fs_node *raw_node;
	int nr_free = 0, ofs = dn->ofs_in_node, len = count;
	__le32 *addr;
	int base = 0;

	if (IS_INODE(dn->node_page) && f2fs_has_extra_attr(dn->inode))
		base = get_extra_isize(dn->inode);

	raw_node = F2FS_NODE(dn->node_page);
	addr = blkaddr_in_node(raw_node) + base + ofs;

	for (; count > 0; count--, addr++, dn->ofs_in_node++) {
		block_t blkaddr = le32_to_cpu(*addr);

		if (blkaddr == NULL_ADDR)
			continue;

		dn->data_blkaddr = NULL_ADDR;
		f2fs_set_data_blkaddr(dn);

		if (__is_valid_data_blkaddr(blkaddr) &&
			!f2fs_is_valid_blkaddr(sbi, blkaddr,
					DATA_GENERIC_ENHANCE))
			continue;

		f2fs_invalidate_blocks(sbi, blkaddr);
		if (dn->ofs_in_node == 0 && IS_INODE(dn->node_page))
			clear_inode_flag(dn->inode, FI_FIRST_BLOCK_WRITTEN);
		nr_free++;
	}

	if (nr_free) {
		pgoff_t fofs;
		/*
		 * once we invalidate valid blkaddr in range [ofs, ofs + count],
		 * we will invalidate all blkaddr in the whole range.
		 */
		fofs = f2fs_start_bidx_of_node(ofs_of_node(dn->node_page),
							dn->inode) + ofs;
		f2fs_update_extent_cache_range(dn, fofs, 0, len);
		dec_valid_block_count(sbi, dn->inode, nr_free);
	}
	dn->ofs_in_node = ofs;

	f2fs_update_time(sbi, REQ_TIME);
	trace_f2fs_truncate_data_blocks_range(dn->inode, dn->nid,
					 dn->ofs_in_node, nr_free);
}