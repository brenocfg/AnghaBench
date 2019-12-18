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
struct page {scalar_t__ mapping; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode {scalar_t__* i_nid; } ;
struct dnode_of_data {int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int NIDS_PER_BLOCK ; 
 int /*<<< orphan*/  NODE ; 
#define  NODE_DIND_BLOCK 132 
#define  NODE_DIR1_BLOCK 131 
#define  NODE_DIR2_BLOCK 130 
#define  NODE_IND1_BLOCK 129 
#define  NODE_IND2_BLOCK 128 
 scalar_t__ NODE_MAPPING (struct f2fs_sb_info*) ; 
 int PTR_ERR (struct page*) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int get_node_path (struct inode*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,struct page*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  trace_f2fs_truncate_inode_blocks_enter (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_truncate_inode_blocks_exit (struct inode*,int) ; 
 int truncate_dnode (struct dnode_of_data*) ; 
 int truncate_nodes (struct dnode_of_data*,unsigned int,int,int) ; 
 int truncate_partial_nodes (struct dnode_of_data*,struct f2fs_inode*,int*,int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int f2fs_truncate_inode_blocks(struct inode *inode, pgoff_t from)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int err = 0, cont = 1;
	int level, offset[4], noffset[4];
	unsigned int nofs = 0;
	struct f2fs_inode *ri;
	struct dnode_of_data dn;
	struct page *page;

	trace_f2fs_truncate_inode_blocks_enter(inode, from);

	level = get_node_path(inode, from, offset, noffset);
	if (level < 0)
		return level;

	page = f2fs_get_node_page(sbi, inode->i_ino);
	if (IS_ERR(page)) {
		trace_f2fs_truncate_inode_blocks_exit(inode, PTR_ERR(page));
		return PTR_ERR(page);
	}

	set_new_dnode(&dn, inode, page, NULL, 0);
	unlock_page(page);

	ri = F2FS_INODE(page);
	switch (level) {
	case 0:
	case 1:
		nofs = noffset[1];
		break;
	case 2:
		nofs = noffset[1];
		if (!offset[level - 1])
			goto skip_partial;
		err = truncate_partial_nodes(&dn, ri, offset, level);
		if (err < 0 && err != -ENOENT)
			goto fail;
		nofs += 1 + NIDS_PER_BLOCK;
		break;
	case 3:
		nofs = 5 + 2 * NIDS_PER_BLOCK;
		if (!offset[level - 1])
			goto skip_partial;
		err = truncate_partial_nodes(&dn, ri, offset, level);
		if (err < 0 && err != -ENOENT)
			goto fail;
		break;
	default:
		BUG();
	}

skip_partial:
	while (cont) {
		dn.nid = le32_to_cpu(ri->i_nid[offset[0] - NODE_DIR1_BLOCK]);
		switch (offset[0]) {
		case NODE_DIR1_BLOCK:
		case NODE_DIR2_BLOCK:
			err = truncate_dnode(&dn);
			break;

		case NODE_IND1_BLOCK:
		case NODE_IND2_BLOCK:
			err = truncate_nodes(&dn, nofs, offset[1], 2);
			break;

		case NODE_DIND_BLOCK:
			err = truncate_nodes(&dn, nofs, offset[1], 3);
			cont = 0;
			break;

		default:
			BUG();
		}
		if (err < 0 && err != -ENOENT)
			goto fail;
		if (offset[1] == 0 &&
				ri->i_nid[offset[0] - NODE_DIR1_BLOCK]) {
			lock_page(page);
			BUG_ON(page->mapping != NODE_MAPPING(sbi));
			f2fs_wait_on_page_writeback(page, NODE, true, true);
			ri->i_nid[offset[0] - NODE_DIR1_BLOCK] = 0;
			set_page_dirty(page);
			unlock_page(page);
		}
		offset[1] = 0;
		offset[0]++;
		nofs += err;
	}
fail:
	f2fs_put_page(page, 0);
	trace_f2fs_truncate_inode_blocks_exit(inode, err);
	return err > 0 ? 0 : err;
}