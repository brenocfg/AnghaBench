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
struct dnode_of_data {int node_changed; int /*<<< orphan*/  node_page; int /*<<< orphan*/  data_blkaddr; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  inode; int /*<<< orphan*/  nid; } ;
typedef  scalar_t__ block_t ;
typedef  int /*<<< orphan*/  blkcnt_t ;

/* Variables and functions */
 int EPERM ; 
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FI_NO_ALLOC ; 
 int /*<<< orphan*/  NEW_ADDR ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  __set_data_blkaddr (struct dnode_of_data*) ; 
 scalar_t__ datablock_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int inc_valid_block_count (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int is_inode_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ set_page_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_reserve_new_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int f2fs_reserve_new_blocks(struct dnode_of_data *dn, blkcnt_t count)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	int err;

	if (!count)
		return 0;

	if (unlikely(is_inode_flag_set(dn->inode, FI_NO_ALLOC)))
		return -EPERM;
	if (unlikely((err = inc_valid_block_count(sbi, dn->inode, &count))))
		return err;

	trace_f2fs_reserve_new_blocks(dn->inode, dn->nid,
						dn->ofs_in_node, count);

	f2fs_wait_on_page_writeback(dn->node_page, NODE, true, true);

	for (; count > 0; dn->ofs_in_node++) {
		block_t blkaddr = datablock_addr(dn->inode,
					dn->node_page, dn->ofs_in_node);
		if (blkaddr == NULL_ADDR) {
			dn->data_blkaddr = NEW_ADDR;
			__set_data_blkaddr(dn);
			count--;
		}
	}

	if (set_page_dirty(dn->node_page))
		dn->node_changed = true;
	return 0;
}