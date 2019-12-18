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
struct dnode_of_data {unsigned int ofs_in_node; scalar_t__ data_blkaddr; int /*<<< orphan*/  node_page; int /*<<< orphan*/  inode; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ blkcnt_t ;

/* Variables and functions */
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ NEW_ADDR ; 
 scalar_t__ NULL_ADDR ; 
 scalar_t__ datablock_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  f2fs_invalidate_blocks (struct f2fs_sb_info*,scalar_t__) ; 
 int f2fs_reserve_new_blocks (struct dnode_of_data*,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_set_data_blkaddr (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_update_extent_cache_range (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int f2fs_do_zero_range(struct dnode_of_data *dn, pgoff_t start,
								pgoff_t end)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	pgoff_t index = start;
	unsigned int ofs_in_node = dn->ofs_in_node;
	blkcnt_t count = 0;
	int ret;

	for (; index < end; index++, dn->ofs_in_node++) {
		if (datablock_addr(dn->inode, dn->node_page,
					dn->ofs_in_node) == NULL_ADDR)
			count++;
	}

	dn->ofs_in_node = ofs_in_node;
	ret = f2fs_reserve_new_blocks(dn, count);
	if (ret)
		return ret;

	dn->ofs_in_node = ofs_in_node;
	for (index = start; index < end; index++, dn->ofs_in_node++) {
		dn->data_blkaddr = datablock_addr(dn->inode,
					dn->node_page, dn->ofs_in_node);
		/*
		 * f2fs_reserve_new_blocks will not guarantee entire block
		 * allocation.
		 */
		if (dn->data_blkaddr == NULL_ADDR) {
			ret = -ENOSPC;
			break;
		}
		if (dn->data_blkaddr != NEW_ADDR) {
			f2fs_invalidate_blocks(sbi, dn->data_blkaddr);
			dn->data_blkaddr = NEW_ADDR;
			f2fs_set_data_blkaddr(dn);
		}
	}

	f2fs_update_extent_cache_range(dn, start, 0, index - start);

	return ret;
}