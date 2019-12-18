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
struct node_info {int /*<<< orphan*/  version; } ;
struct f2fs_summary {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {int /*<<< orphan*/  data_blkaddr; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; int /*<<< orphan*/  inode; int /*<<< orphan*/  node_page; } ;
typedef  int /*<<< orphan*/  block_t ;
typedef  int blkcnt_t ;

/* Variables and functions */
 int EPERM ; 
 struct f2fs_sb_info* F2FS_I_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FI_NO_ALLOC ; 
 scalar_t__ GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  META_MAPPING (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  NULL_ADDR ; 
 scalar_t__ NULL_SEGNO ; 
 int /*<<< orphan*/  datablock_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_allocate_data_block (struct f2fs_sb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct f2fs_summary*,int,int /*<<< orphan*/ *,int) ; 
 int f2fs_get_node_info (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct node_info*) ; 
 int /*<<< orphan*/  f2fs_update_data_blkaddr (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int inc_valid_block_count (struct f2fs_sb_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_inode_flag_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_summary (struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __allocate_data_block(struct dnode_of_data *dn, int seg_type)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	struct f2fs_summary sum;
	struct node_info ni;
	block_t old_blkaddr;
	blkcnt_t count = 1;
	int err;

	if (unlikely(is_inode_flag_set(dn->inode, FI_NO_ALLOC)))
		return -EPERM;

	err = f2fs_get_node_info(sbi, dn->nid, &ni);
	if (err)
		return err;

	dn->data_blkaddr = datablock_addr(dn->inode,
				dn->node_page, dn->ofs_in_node);
	if (dn->data_blkaddr != NULL_ADDR)
		goto alloc;

	if (unlikely((err = inc_valid_block_count(sbi, dn->inode, &count))))
		return err;

alloc:
	set_summary(&sum, dn->nid, dn->ofs_in_node, ni.version);
	old_blkaddr = dn->data_blkaddr;
	f2fs_allocate_data_block(sbi, NULL, old_blkaddr, &dn->data_blkaddr,
					&sum, seg_type, NULL, false);
	if (GET_SEGNO(sbi, old_blkaddr) != NULL_SEGNO)
		invalidate_mapping_pages(META_MAPPING(sbi),
					old_blkaddr, old_blkaddr);
	f2fs_update_data_blkaddr(dn, dn->data_blkaddr);

	/*
	 * i_size will be updated by direct_IO. Otherwise, we'll get stale
	 * data from unwritten block via dio_read.
	 */
	return 0;
}