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
struct page {int dummy; } ;
struct node_info {int /*<<< orphan*/  blk_addr; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_xattr_nid; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  F2FS_NODE (struct page*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  NULL_ADDR ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  VALID_XATTR_BLOCK_SIZE ; 
 int /*<<< orphan*/  XATTR_NODE_OFFSET ; 
 int /*<<< orphan*/  dec_valid_node_count (struct f2fs_sb_info*,struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_alloc_nid (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_done (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_failed (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int f2fs_get_node_info (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct node_info*) ; 
 int /*<<< orphan*/  f2fs_invalidate_blocks (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_new_node_page (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_update_inode_page (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_node_addr (struct f2fs_sb_info*,struct node_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

int f2fs_recover_xattr_data(struct inode *inode, struct page *page)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t prev_xnid = F2FS_I(inode)->i_xattr_nid;
	nid_t new_xnid;
	struct dnode_of_data dn;
	struct node_info ni;
	struct page *xpage;
	int err;

	if (!prev_xnid)
		goto recover_xnid;

	/* 1: invalidate the previous xattr nid */
	err = f2fs_get_node_info(sbi, prev_xnid, &ni);
	if (err)
		return err;

	f2fs_invalidate_blocks(sbi, ni.blk_addr);
	dec_valid_node_count(sbi, inode, false);
	set_node_addr(sbi, &ni, NULL_ADDR, false);

recover_xnid:
	/* 2: update xattr nid in inode */
	if (!f2fs_alloc_nid(sbi, &new_xnid))
		return -ENOSPC;

	set_new_dnode(&dn, inode, NULL, NULL, new_xnid);
	xpage = f2fs_new_node_page(&dn, XATTR_NODE_OFFSET);
	if (IS_ERR(xpage)) {
		f2fs_alloc_nid_failed(sbi, new_xnid);
		return PTR_ERR(xpage);
	}

	f2fs_alloc_nid_done(sbi, new_xnid);
	f2fs_update_inode_page(inode);

	/* 3: update and set xattr node page dirty */
	memcpy(F2FS_NODE(xpage), F2FS_NODE(page), VALID_XATTR_BLOCK_SIZE);

	set_page_dirty(xpage);
	f2fs_put_page(xpage, 1);

	return 0;
}