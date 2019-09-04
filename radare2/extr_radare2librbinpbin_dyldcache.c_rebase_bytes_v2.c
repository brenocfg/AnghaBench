#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  size_t ut64 ;
typedef  int ut32 ;
typedef  int ut16 ;
struct TYPE_3__ {size_t start_of_data; size_t page_size; size_t page_starts_count; int* page_starts; size_t delta_mask; size_t delta_shift; size_t value_mask; size_t value_add; size_t slide; } ;
typedef  TYPE_1__ RDyldRebaseInfo2 ;

/* Variables and functions */
 int DYLD_CACHE_SLIDE_PAGE_ATTR_EXTRA ; 
 int DYLD_CACHE_SLIDE_PAGE_ATTR_NO_REBASE ; 
 size_t r_read_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_write_le64 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void rebase_bytes_v2(RDyldRebaseInfo2 *rebase_info, ut8 *buf, ut64 offset, int count, ut64 start_of_write) {
	int in_buf = 0;
	while (in_buf < count) {
		ut64 offset_in_data = offset - rebase_info->start_of_data;
		ut64 page_index = offset_in_data / rebase_info->page_size;
		ut64 page_offset = offset_in_data % rebase_info->page_size;
		ut64 to_next_page = rebase_info->page_size - page_offset;

		if (page_index >= rebase_info->page_starts_count) {
			goto next_page;
		}
		ut16 page_flag = rebase_info->page_starts[page_index];

		if (page_flag == DYLD_CACHE_SLIDE_PAGE_ATTR_NO_REBASE) {
			goto next_page;
		}

		if (!(page_flag & DYLD_CACHE_SLIDE_PAGE_ATTR_EXTRA)) {
			ut64 first_rebase_off = rebase_info->page_starts[page_index] * 4;
			if (first_rebase_off >= page_offset && first_rebase_off < page_offset + count) {
				ut32 delta = 1;
				while (delta) {
					ut64 position = in_buf + first_rebase_off - page_offset;
					if (position >= count) {
						break;
					}
					ut64 raw_value = r_read_le64 (buf + position);
					delta = ((raw_value & rebase_info->delta_mask) >> rebase_info->delta_shift);
					if (position >= start_of_write) {
						ut64 new_value = raw_value & rebase_info->value_mask;
						if (new_value != 0) {
							new_value += rebase_info->value_add;
							new_value += rebase_info->slide;
						}
						r_write_le64 (buf + position, new_value);
					}
					first_rebase_off += delta;
				}
			}
		}
next_page:
		in_buf += to_next_page;
		offset += to_next_page;
	}
}