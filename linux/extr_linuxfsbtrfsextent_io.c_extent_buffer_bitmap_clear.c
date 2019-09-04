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
typedef  int /*<<< orphan*/  u8 ;
struct page {int dummy; } ;
struct extent_buffer {struct page** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_FIRST_BYTE_MASK (unsigned long) ; 
 int /*<<< orphan*/  BITMAP_LAST_BYTE_MASK (unsigned int const) ; 
 unsigned long BITS_PER_BYTE ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  eb_bitmap_offset (struct extent_buffer*,unsigned long,unsigned long,unsigned long*,size_t*) ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 

void extent_buffer_bitmap_clear(struct extent_buffer *eb, unsigned long start,
				unsigned long pos, unsigned long len)
{
	u8 *kaddr;
	struct page *page;
	unsigned long i;
	size_t offset;
	const unsigned int size = pos + len;
	int bits_to_clear = BITS_PER_BYTE - (pos % BITS_PER_BYTE);
	u8 mask_to_clear = BITMAP_FIRST_BYTE_MASK(pos);

	eb_bitmap_offset(eb, start, pos, &i, &offset);
	page = eb->pages[i];
	WARN_ON(!PageUptodate(page));
	kaddr = page_address(page);

	while (len >= bits_to_clear) {
		kaddr[offset] &= ~mask_to_clear;
		len -= bits_to_clear;
		bits_to_clear = BITS_PER_BYTE;
		mask_to_clear = ~0;
		if (++offset >= PAGE_SIZE && len > 0) {
			offset = 0;
			page = eb->pages[++i];
			WARN_ON(!PageUptodate(page));
			kaddr = page_address(page);
		}
	}
	if (len) {
		mask_to_clear &= BITMAP_LAST_BYTE_MASK(size);
		kaddr[offset] &= ~mask_to_clear;
	}
}