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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode {int i_inline; } ;

/* Variables and functions */
 int F2FS_INLINE_DATA ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  FI_INLINE_DATA ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 scalar_t__ IS_INODE (struct page*) ; 
 int /*<<< orphan*/  MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 scalar_t__ f2fs_truncate_blocks (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_truncate_inline_inode (struct inode*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

bool f2fs_recover_inline_data(struct inode *inode, struct page *npage)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct f2fs_inode *ri = NULL;
	void *src_addr, *dst_addr;
	struct page *ipage;

	/*
	 * The inline_data recovery policy is as follows.
	 * [prev.] [next] of inline_data flag
	 *    o       o  -> recover inline_data
	 *    o       x  -> remove inline_data, and then recover data blocks
	 *    x       o  -> remove inline_data, and then recover inline_data
	 *    x       x  -> recover data blocks
	 */
	if (IS_INODE(npage))
		ri = F2FS_INODE(npage);

	if (f2fs_has_inline_data(inode) &&
			ri && (ri->i_inline & F2FS_INLINE_DATA)) {
process_inline:
		ipage = f2fs_get_node_page(sbi, inode->i_ino);
		f2fs_bug_on(sbi, IS_ERR(ipage));

		f2fs_wait_on_page_writeback(ipage, NODE, true, true);

		src_addr = inline_data_addr(inode, npage);
		dst_addr = inline_data_addr(inode, ipage);
		memcpy(dst_addr, src_addr, MAX_INLINE_DATA(inode));

		set_inode_flag(inode, FI_INLINE_DATA);
		set_inode_flag(inode, FI_DATA_EXIST);

		set_page_dirty(ipage);
		f2fs_put_page(ipage, 1);
		return true;
	}

	if (f2fs_has_inline_data(inode)) {
		ipage = f2fs_get_node_page(sbi, inode->i_ino);
		f2fs_bug_on(sbi, IS_ERR(ipage));
		f2fs_truncate_inline_inode(inode, ipage, 0);
		clear_inode_flag(inode, FI_INLINE_DATA);
		f2fs_put_page(ipage, 1);
	} else if (ri && (ri->i_inline & F2FS_INLINE_DATA)) {
		if (f2fs_truncate_blocks(inode, 0, false))
			return false;
		goto process_inline;
	}
	return false;
}