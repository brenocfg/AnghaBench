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
struct inode {scalar_t__ i_ino; } ;
struct f2fs_sb_info {int dummy; } ;
struct dnode_of_data {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  size_t __u32 ;
struct TYPE_2__ {scalar_t__ i_xattr_nid; } ;

/* Variables and functions */
 int ENOSPC ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int PTR_ERR (struct page*) ; 
 size_t VALID_XATTR_BLOCK_SIZE ; 
 int /*<<< orphan*/  XATTR_NODE_OFFSET ; 
 int /*<<< orphan*/  f2fs_alloc_nid (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_done (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_failed (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct page* f2fs_get_node_page (struct f2fs_sb_info*,scalar_t__) ; 
 struct page* f2fs_new_node_page (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int f2fs_truncate_xattr_node (struct inode*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_xattr_addr (struct inode*,struct page*) ; 
 size_t inline_xattr_size (struct inode*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static inline int write_all_xattrs(struct inode *inode, __u32 hsize,
				void *txattr_addr, struct page *ipage)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	size_t inline_size = inline_xattr_size(inode);
	struct page *in_page = NULL;
	void *xattr_addr;
	void *inline_addr = NULL;
	struct page *xpage;
	nid_t new_nid = 0;
	int err = 0;

	if (hsize > inline_size && !F2FS_I(inode)->i_xattr_nid)
		if (!f2fs_alloc_nid(sbi, &new_nid))
			return -ENOSPC;

	/* write to inline xattr */
	if (inline_size) {
		if (ipage) {
			inline_addr = inline_xattr_addr(inode, ipage);
		} else {
			in_page = f2fs_get_node_page(sbi, inode->i_ino);
			if (IS_ERR(in_page)) {
				f2fs_alloc_nid_failed(sbi, new_nid);
				return PTR_ERR(in_page);
			}
			inline_addr = inline_xattr_addr(inode, in_page);
		}

		f2fs_wait_on_page_writeback(ipage ? ipage : in_page,
							NODE, true, true);
		/* no need to use xattr node block */
		if (hsize <= inline_size) {
			err = f2fs_truncate_xattr_node(inode);
			f2fs_alloc_nid_failed(sbi, new_nid);
			if (err) {
				f2fs_put_page(in_page, 1);
				return err;
			}
			memcpy(inline_addr, txattr_addr, inline_size);
			set_page_dirty(ipage ? ipage : in_page);
			goto in_page_out;
		}
	}

	/* write to xattr node block */
	if (F2FS_I(inode)->i_xattr_nid) {
		xpage = f2fs_get_node_page(sbi, F2FS_I(inode)->i_xattr_nid);
		if (IS_ERR(xpage)) {
			err = PTR_ERR(xpage);
			f2fs_alloc_nid_failed(sbi, new_nid);
			goto in_page_out;
		}
		f2fs_bug_on(sbi, new_nid);
		f2fs_wait_on_page_writeback(xpage, NODE, true, true);
	} else {
		struct dnode_of_data dn;
		set_new_dnode(&dn, inode, NULL, NULL, new_nid);
		xpage = f2fs_new_node_page(&dn, XATTR_NODE_OFFSET);
		if (IS_ERR(xpage)) {
			err = PTR_ERR(xpage);
			f2fs_alloc_nid_failed(sbi, new_nid);
			goto in_page_out;
		}
		f2fs_alloc_nid_done(sbi, new_nid);
	}
	xattr_addr = page_address(xpage);

	if (inline_size)
		memcpy(inline_addr, txattr_addr, inline_size);
	memcpy(xattr_addr, txattr_addr + inline_size, VALID_XATTR_BLOCK_SIZE);

	if (inline_size)
		set_page_dirty(ipage ? ipage : in_page);
	set_page_dirty(xpage);

	f2fs_put_page(xpage, 1);
in_page_out:
	f2fs_put_page(in_page, 1);
	return err;
}