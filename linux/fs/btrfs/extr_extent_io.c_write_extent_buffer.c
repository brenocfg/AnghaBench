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
struct extent_buffer {size_t start; unsigned long len; struct page** pages; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t min (unsigned long,scalar_t__) ; 
 size_t offset_in_page (size_t) ; 
 char* page_address (struct page*) ; 

void write_extent_buffer(struct extent_buffer *eb, const void *srcv,
			 unsigned long start, unsigned long len)
{
	size_t cur;
	size_t offset;
	struct page *page;
	char *kaddr;
	char *src = (char *)srcv;
	size_t start_offset = offset_in_page(eb->start);
	unsigned long i = (start_offset + start) >> PAGE_SHIFT;

	WARN_ON(start > eb->len);
	WARN_ON(start + len > eb->start + eb->len);

	offset = offset_in_page(start_offset + start);

	while (len > 0) {
		page = eb->pages[i];
		WARN_ON(!PageUptodate(page));

		cur = min(len, PAGE_SIZE - offset);
		kaddr = page_address(page);
		memcpy(kaddr + offset, src, cur);

		src += cur;
		len -= cur;
		offset = 0;
		i++;
	}
}