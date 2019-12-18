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
struct f2fs_inode {int i_inline; } ;

/* Variables and functions */
 int F2FS_INLINE_XATTR ; 
 struct f2fs_inode* F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_INLINE_XATTR ; 
 int /*<<< orphan*/  IS_ERR (struct page*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* f2fs_get_node_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int) ; 
 int /*<<< orphan*/  f2fs_update_inode (struct inode*,struct page*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_xattr_addr (struct inode*,struct page*) ; 
 size_t inline_xattr_size (struct inode*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

void f2fs_recover_inline_xattr(struct inode *inode, struct page *page)
{
	void *src_addr, *dst_addr;
	size_t inline_size;
	struct page *ipage;
	struct f2fs_inode *ri;

	ipage = f2fs_get_node_page(F2FS_I_SB(inode), inode->i_ino);
	f2fs_bug_on(F2FS_I_SB(inode), IS_ERR(ipage));

	ri = F2FS_INODE(page);
	if (ri->i_inline & F2FS_INLINE_XATTR) {
		set_inode_flag(inode, FI_INLINE_XATTR);
	} else {
		clear_inode_flag(inode, FI_INLINE_XATTR);
		goto update_inode;
	}

	dst_addr = inline_xattr_addr(inode, ipage);
	src_addr = inline_xattr_addr(inode, page);
	inline_size = inline_xattr_size(inode);

	f2fs_wait_on_page_writeback(ipage, NODE, true, true);
	memcpy(dst_addr, src_addr, inline_size);
update_inode:
	f2fs_update_inode(inode, ipage);
	f2fs_put_page(ipage, 1);
}