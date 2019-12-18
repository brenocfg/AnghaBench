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
struct ocfs2_reservation_map {int /*<<< orphan*/  m_bitmap_len; void* m_disk_bitmap; } ;

/* Variables and functions */
 int ocfs2_find_next_zero_bit (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_ocfs2_resmap_find_free_bits_begin (unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_resmap_find_free_bits_end (unsigned int,unsigned int) ; 

__attribute__((used)) static int ocfs2_resmap_find_free_bits(struct ocfs2_reservation_map *resmap,
				       unsigned int wanted,
				       unsigned int search_start,
				       unsigned int search_len,
				       unsigned int *rstart,
				       unsigned int *rlen)
{
	void *bitmap = resmap->m_disk_bitmap;
	unsigned int best_start, best_len = 0;
	int offset, start, found;

	trace_ocfs2_resmap_find_free_bits_begin(search_start, search_len,
						wanted, resmap->m_bitmap_len);

	found = best_start = best_len = 0;

	start = search_start;
	while ((offset = ocfs2_find_next_zero_bit(bitmap, resmap->m_bitmap_len,
						 start)) != -1) {
		/* Search reached end of the region */
		if (offset >= (search_start + search_len))
			break;

		if (offset == start) {
			/* we found a zero */
			found++;
			/* move start to the next bit to test */
			start++;
		} else {
			/* got a zero after some ones */
			found = 1;
			start = offset + 1;
		}
		if (found > best_len) {
			best_len = found;
			best_start = start - found;
		}

		if (found >= wanted)
			break;
	}

	if (best_len == 0)
		return 0;

	if (best_len >= wanted)
		best_len = wanted;

	*rlen = best_len;
	*rstart = best_start;

	trace_ocfs2_resmap_find_free_bits_end(best_start, best_len);

	return *rlen;
}