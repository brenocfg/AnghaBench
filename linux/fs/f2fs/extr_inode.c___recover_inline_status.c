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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_INODE (struct page*) ; 
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 int MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_raw_inline (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __recover_inline_status(struct inode *inode, struct page *ipage)
{
	void *inline_data = inline_data_addr(inode, ipage);
	__le32 *start = inline_data;
	__le32 *end = start + MAX_INLINE_DATA(inode) / sizeof(__le32);

	while (start < end) {
		if (*start++) {
			f2fs_wait_on_page_writeback(ipage, NODE, true, true);

			set_inode_flag(inode, FI_DATA_EXIST);
			set_raw_inline(inode, F2FS_INODE(ipage));
			set_page_dirty(ipage);
			return;
		}
	}
	return;
}