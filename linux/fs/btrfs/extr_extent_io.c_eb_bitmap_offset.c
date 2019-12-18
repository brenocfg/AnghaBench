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
struct extent_buffer {size_t start; } ;

/* Variables and functions */
 size_t BIT_BYTE (unsigned long) ; 
 size_t PAGE_SHIFT ; 
 size_t offset_in_page (size_t) ; 

__attribute__((used)) static inline void eb_bitmap_offset(struct extent_buffer *eb,
				    unsigned long start, unsigned long nr,
				    unsigned long *page_index,
				    size_t *page_offset)
{
	size_t start_offset = offset_in_page(eb->start);
	size_t byte_offset = BIT_BYTE(nr);
	size_t offset;

	/*
	 * The byte we want is the offset of the extent buffer + the offset of
	 * the bitmap item in the extent buffer + the offset of the byte in the
	 * bitmap item.
	 */
	offset = start_offset + start + byte_offset;

	*page_index = offset >> PAGE_SHIFT;
	*page_offset = offset_in_page(offset);
}