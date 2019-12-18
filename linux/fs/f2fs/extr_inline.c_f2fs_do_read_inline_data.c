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
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 int /*<<< orphan*/  MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  f2fs_bug_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* inline_data_addr (struct inode*,struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void f2fs_do_read_inline_data(struct page *page, struct page *ipage)
{
	struct inode *inode = page->mapping->host;
	void *src_addr, *dst_addr;

	if (PageUptodate(page))
		return;

	f2fs_bug_on(F2FS_P_SB(page), page->index);

	zero_user_segment(page, MAX_INLINE_DATA(inode), PAGE_SIZE);

	/* Copy the whole inline data block */
	src_addr = inline_data_addr(inode, ipage);
	dst_addr = kmap_atomic(page);
	memcpy(dst_addr, src_addr, MAX_INLINE_DATA(inode));
	flush_dcache_page(page);
	kunmap_atomic(dst_addr);
	if (!PageUptodate(page))
		SetPageUptodate(page);
}