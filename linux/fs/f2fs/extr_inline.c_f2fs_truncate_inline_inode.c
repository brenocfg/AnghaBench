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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FI_DATA_EXIST ; 
 scalar_t__ MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void f2fs_truncate_inline_inode(struct inode *inode,
					struct page *ipage, u64 from)
{
	void *addr;

	if (from >= MAX_INLINE_DATA(inode))
		return;

	addr = inline_data_addr(inode, ipage);

	f2fs_wait_on_page_writeback(ipage, NODE, true, true);
	memset(addr + from, 0, MAX_INLINE_DATA(inode) - from);
	set_page_dirty(ipage);

	if (from == 0)
		clear_inode_flag(inode, FI_DATA_EXIST);
}