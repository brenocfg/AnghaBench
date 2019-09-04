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
struct page {int index; } ;
struct iomap {int /*<<< orphan*/  inline_data; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t PAGE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 size_t i_size_read (struct inode*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iomap_read_inline_data(struct inode *inode, struct page *page,
		struct iomap *iomap)
{
	size_t size = i_size_read(inode);
	void *addr;

	if (PageUptodate(page))
		return;

	BUG_ON(page->index);
	BUG_ON(size > PAGE_SIZE - offset_in_page(iomap->inline_data));

	addr = kmap_atomic(page);
	memcpy(addr, iomap->inline_data, size);
	memset(addr + size, 0, PAGE_SIZE - size);
	kunmap_atomic(addr);
	SetPageUptodate(page);
}