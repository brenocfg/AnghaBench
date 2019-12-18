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
struct node_info {scalar_t__ ino; int /*<<< orphan*/  version; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {struct page* node_page; int /*<<< orphan*/  nid; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  inode; } ;
typedef  int loff_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 unsigned int ADDRS_PER_PAGE (struct page*,struct inode*) ; 
 int /*<<< orphan*/  ALLOC_NODE ; 
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  CONFIG_F2FS_FAULT_INJECTION ; 
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 int HZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_INODE (struct page*) ; 
 int /*<<< orphan*/  META_POR ; 
 scalar_t__ NEW_ADDR ; 
 int /*<<< orphan*/  NODE ; 
 scalar_t__ NULL_ADDR ; 
 int PAGE_SHIFT ; 
 scalar_t__ __is_valid_data_blkaddr (scalar_t__) ; 
 int check_index_in_prev_nodes (struct f2fs_sb_info*,scalar_t__,struct dnode_of_data*) ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_node_footer (struct page*,struct page*) ; 
 scalar_t__ datablock_addr (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,unsigned int,int /*<<< orphan*/ ) ; 
 int f2fs_get_node_info (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct node_info*) ; 
 scalar_t__ f2fs_has_xattr_block (scalar_t__) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int) ; 
 scalar_t__ f2fs_is_valid_blkaddr (struct f2fs_sb_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_notice (struct f2fs_sb_info*,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 scalar_t__ f2fs_recover_inline_data (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_recover_inline_xattr (struct inode*,struct page*) ; 
 int f2fs_recover_xattr_data (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_replace_block (struct f2fs_sb_info*,struct dnode_of_data*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int f2fs_reserve_new_block (struct dnode_of_data*) ; 
 unsigned int f2fs_start_bidx_of_node (scalar_t__,struct inode*) ; 
 int /*<<< orphan*/  f2fs_truncate_data_blocks_range (struct dnode_of_data*,int) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ file_keep_isize (struct inode*) ; 
 int /*<<< orphan*/  fill_node_footer (struct page*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int i_size_read (struct inode*) ; 
 scalar_t__ ino_of_node (struct page*) ; 
 scalar_t__ ofs_of_node (struct page*) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static int do_recover_data(struct f2fs_sb_info *sbi, struct inode *inode,
					struct page *page)
{
	struct dnode_of_data dn;
	struct node_info ni;
	unsigned int start, end;
	int err = 0, recovered = 0;

	/* step 1: recover xattr */
	if (IS_INODE(page)) {
		f2fs_recover_inline_xattr(inode, page);
	} else if (f2fs_has_xattr_block(ofs_of_node(page))) {
		err = f2fs_recover_xattr_data(inode, page);
		if (!err)
			recovered++;
		goto out;
	}

	/* step 2: recover inline data */
	if (f2fs_recover_inline_data(inode, page))
		goto out;

	/* step 3: recover data indices */
	start = f2fs_start_bidx_of_node(ofs_of_node(page), inode);
	end = start + ADDRS_PER_PAGE(page, inode);

	set_new_dnode(&dn, inode, NULL, NULL, 0);
retry_dn:
	err = f2fs_get_dnode_of_data(&dn, start, ALLOC_NODE);
	if (err) {
		if (err == -ENOMEM) {
			congestion_wait(BLK_RW_ASYNC, HZ/50);
			goto retry_dn;
		}
		goto out;
	}

	f2fs_wait_on_page_writeback(dn.node_page, NODE, true, true);

	err = f2fs_get_node_info(sbi, dn.nid, &ni);
	if (err)
		goto err;

	f2fs_bug_on(sbi, ni.ino != ino_of_node(page));

	if (ofs_of_node(dn.node_page) != ofs_of_node(page)) {
		f2fs_warn(sbi, "Inconsistent ofs_of_node, ino:%lu, ofs:%u, %u",
			  inode->i_ino, ofs_of_node(dn.node_page),
			  ofs_of_node(page));
		err = -EFSCORRUPTED;
		goto err;
	}

	for (; start < end; start++, dn.ofs_in_node++) {
		block_t src, dest;

		src = datablock_addr(dn.inode, dn.node_page, dn.ofs_in_node);
		dest = datablock_addr(dn.inode, page, dn.ofs_in_node);

		if (__is_valid_data_blkaddr(src) &&
			!f2fs_is_valid_blkaddr(sbi, src, META_POR)) {
			err = -EFSCORRUPTED;
			goto err;
		}

		if (__is_valid_data_blkaddr(dest) &&
			!f2fs_is_valid_blkaddr(sbi, dest, META_POR)) {
			err = -EFSCORRUPTED;
			goto err;
		}

		/* skip recovering if dest is the same as src */
		if (src == dest)
			continue;

		/* dest is invalid, just invalidate src block */
		if (dest == NULL_ADDR) {
			f2fs_truncate_data_blocks_range(&dn, 1);
			continue;
		}

		if (!file_keep_isize(inode) &&
			(i_size_read(inode) <= ((loff_t)start << PAGE_SHIFT)))
			f2fs_i_size_write(inode,
				(loff_t)(start + 1) << PAGE_SHIFT);

		/*
		 * dest is reserved block, invalidate src block
		 * and then reserve one new block in dnode page.
		 */
		if (dest == NEW_ADDR) {
			f2fs_truncate_data_blocks_range(&dn, 1);
			f2fs_reserve_new_block(&dn);
			continue;
		}

		/* dest is valid block, try to recover from src to dest */
		if (f2fs_is_valid_blkaddr(sbi, dest, META_POR)) {

			if (src == NULL_ADDR) {
				err = f2fs_reserve_new_block(&dn);
				while (err &&
				       IS_ENABLED(CONFIG_F2FS_FAULT_INJECTION))
					err = f2fs_reserve_new_block(&dn);
				/* We should not get -ENOSPC */
				f2fs_bug_on(sbi, err);
				if (err)
					goto err;
			}
retry_prev:
			/* Check the previous node page having this index */
			err = check_index_in_prev_nodes(sbi, dest, &dn);
			if (err) {
				if (err == -ENOMEM) {
					congestion_wait(BLK_RW_ASYNC, HZ/50);
					goto retry_prev;
				}
				goto err;
			}

			/* write dummy data page */
			f2fs_replace_block(sbi, &dn, src, dest,
						ni.version, false, false);
			recovered++;
		}
	}

	copy_node_footer(dn.node_page, page);
	fill_node_footer(dn.node_page, dn.nid, ni.ino,
					ofs_of_node(page), false);
	set_page_dirty(dn.node_page);
err:
	f2fs_put_dnode(&dn);
out:
	f2fs_notice(sbi, "recover_data: ino = %lx (i_size: %s) recovered = %d, err = %d",
		    inode->i_ino, file_keep_isize(inode) ? "keep" : "recover",
		    recovered, err);
	return err;
}