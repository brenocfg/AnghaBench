#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {scalar_t__ index; TYPE_1__* mapping; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct extent_info {scalar_t__ blk; scalar_t__ fofs; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dnode_of_data {scalar_t__ data_blkaddr; int node_changed; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
typedef  scalar_t__ block_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int F2FS_GET_BLOCK_DEFAULT ; 
 int F2FS_GET_BLOCK_PRE_AIO ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  FI_NO_PREALLOC ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 unsigned int MAX_INLINE_DATA (struct inode*) ; 
 scalar_t__ NULL_ADDR ; 
 int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __do_map_lock (struct f2fs_sb_info*,int,int) ; 
 int f2fs_convert_inline_page (struct dnode_of_data*,struct page*) ; 
 int /*<<< orphan*/  f2fs_do_read_inline_data (struct page*,struct page*) ; 
 int f2fs_get_block (struct dnode_of_data*,scalar_t__) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 scalar_t__ f2fs_lookup_extent_cache (struct inode*,scalar_t__,struct extent_info*) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_verity_in_progress (struct inode*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inline_node (struct page*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,struct page*,struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_write_begin(struct f2fs_sb_info *sbi,
			struct page *page, loff_t pos, unsigned len,
			block_t *blk_addr, bool *node_changed)
{
	struct inode *inode = page->mapping->host;
	pgoff_t index = page->index;
	struct dnode_of_data dn;
	struct page *ipage;
	bool locked = false;
	struct extent_info ei = {0,0,0};
	int err = 0;
	int flag;

	/*
	 * we already allocated all the blocks, so we don't need to get
	 * the block addresses when there is no need to fill the page.
	 */
	if (!f2fs_has_inline_data(inode) && len == PAGE_SIZE &&
	    !is_inode_flag_set(inode, FI_NO_PREALLOC) &&
	    !f2fs_verity_in_progress(inode))
		return 0;

	/* f2fs_lock_op avoids race between write CP and convert_inline_page */
	if (f2fs_has_inline_data(inode) && pos + len > MAX_INLINE_DATA(inode))
		flag = F2FS_GET_BLOCK_DEFAULT;
	else
		flag = F2FS_GET_BLOCK_PRE_AIO;

	if (f2fs_has_inline_data(inode) ||
			(pos & PAGE_MASK) >= i_size_read(inode)) {
		__do_map_lock(sbi, flag, true);
		locked = true;
	}
restart:
	/* check inline_data */
	ipage = f2fs_get_node_page(sbi, inode->i_ino);
	if (IS_ERR(ipage)) {
		err = PTR_ERR(ipage);
		goto unlock_out;
	}

	set_new_dnode(&dn, inode, ipage, ipage, 0);

	if (f2fs_has_inline_data(inode)) {
		if (pos + len <= MAX_INLINE_DATA(inode)) {
			f2fs_do_read_inline_data(page, ipage);
			set_inode_flag(inode, FI_DATA_EXIST);
			if (inode->i_nlink)
				set_inline_node(ipage);
		} else {
			err = f2fs_convert_inline_page(&dn, page);
			if (err)
				goto out;
			if (dn.data_blkaddr == NULL_ADDR)
				err = f2fs_get_block(&dn, index);
		}
	} else if (locked) {
		err = f2fs_get_block(&dn, index);
	} else {
		if (f2fs_lookup_extent_cache(inode, index, &ei)) {
			dn.data_blkaddr = ei.blk + index - ei.fofs;
		} else {
			/* hole case */
			err = f2fs_get_dnode_of_data(&dn, index, LOOKUP_NODE);
			if (err || dn.data_blkaddr == NULL_ADDR) {
				f2fs_put_dnode(&dn);
				__do_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO,
								true);
				WARN_ON(flag != F2FS_GET_BLOCK_PRE_AIO);
				locked = true;
				goto restart;
			}
		}
	}

	/* convert_inline_page can make node_changed */
	*blk_addr = dn.data_blkaddr;
	*node_changed = dn.node_changed;
out:
	f2fs_put_dnode(&dn);
unlock_out:
	if (locked)
		__do_map_lock(sbi, flag, false);
	return err;
}