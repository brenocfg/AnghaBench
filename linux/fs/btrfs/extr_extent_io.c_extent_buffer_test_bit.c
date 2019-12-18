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
typedef  unsigned long u8 ;
struct page {int dummy; } ;
struct extent_buffer {struct page** pages; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  eb_bitmap_offset (struct extent_buffer*,unsigned long,unsigned long,unsigned long*,size_t*) ; 
 unsigned long* page_address (struct page*) ; 

int extent_buffer_test_bit(struct extent_buffer *eb, unsigned long start,
			   unsigned long nr)
{
	u8 *kaddr;
	struct page *page;
	unsigned long i;
	size_t offset;

	eb_bitmap_offset(eb, start, nr, &i, &offset);
	page = eb->pages[i];
	WARN_ON(!PageUptodate(page));
	kaddr = page_address(page);
	return 1U & (kaddr[offset] >> (nr & (BITS_PER_BYTE - 1)));
}