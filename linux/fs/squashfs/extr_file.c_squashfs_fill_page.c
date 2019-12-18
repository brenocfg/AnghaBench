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
struct squashfs_cache_entry {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int squashfs_copy_data (void*,struct squashfs_cache_entry*,int,int) ; 

void squashfs_fill_page(struct page *page, struct squashfs_cache_entry *buffer, int offset, int avail)
{
	int copied;
	void *pageaddr;

	pageaddr = kmap_atomic(page);
	copied = squashfs_copy_data(pageaddr, buffer, offset, avail);
	memset(pageaddr + copied, 0, PAGE_SIZE - copied);
	kunmap_atomic(pageaddr);

	flush_dcache_page(page);
	if (copied == avail)
		SetPageUptodate(page);
	else
		SetPageError(page);
}