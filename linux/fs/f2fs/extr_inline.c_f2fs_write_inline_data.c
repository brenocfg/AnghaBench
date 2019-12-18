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
struct page {int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct dnode_of_data {int /*<<< orphan*/  inode_page; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_APPEND_WRITE ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 int /*<<< orphan*/  MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  clear_inline_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_clear_page_cache_dirty_tag (struct page*) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,int /*<<< orphan*/ ) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (int /*<<< orphan*/ ) ; 

int f2fs_write_inline_data(struct inode *inode, struct page *page)
{
	void *src_addr, *dst_addr;
	struct dnode_of_data dn;
	int err;

	set_new_dnode(&dn, inode, NULL, NULL, 0);
	err = f2fs_get_dnode_of_data(&dn, 0, LOOKUP_NODE);
	if (err)
		return err;

	if (!f2fs_has_inline_data(inode)) {
		f2fs_put_dnode(&dn);
		return -EAGAIN;
	}

	f2fs_bug_on(F2FS_I_SB(inode), page->index);

	f2fs_wait_on_page_writeback(dn.inode_page, NODE, true, true);
	src_addr = kmap_atomic(page);
	dst_addr = inline_data_addr(inode, dn.inode_page);
	memcpy(dst_addr, src_addr, MAX_INLINE_DATA(inode));
	kunmap_atomic(src_addr);
	set_page_dirty(dn.inode_page);

	f2fs_clear_page_cache_dirty_tag(page);

	set_inode_flag(inode, FI_APPEND_WRITE);
	set_inode_flag(inode, FI_DATA_EXIST);

	clear_inline_node(dn.inode_page);
	f2fs_put_dnode(&dn);
	return 0;
}