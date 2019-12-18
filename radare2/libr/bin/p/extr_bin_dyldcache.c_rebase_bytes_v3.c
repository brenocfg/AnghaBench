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
struct TYPE_3__ {size_t start_of_data; size_t page_size; size_t page_starts_count; size_t* page_starts; size_t delta_mask; size_t delta_shift; size_t auth_value_add; scalar_t__ slide; } ;
typedef  TYPE_1__ RDyldRebaseInfo3 ;

/* Variables and functions */
 size_t DYLD_CACHE_SLIDE_V3_PAGE_ATTR_NO_REBASE ; 
 scalar_t__ R_IS_PTR_AUTHENTICATED (size_t) ; 
 size_t r_read_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_write_le64 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void rebase_bytes_v3(RDyldRebaseInfo3 *rebase_info, ut8 *buf, ut64 offset, int count, ut64 start_of_write) {
	int in_buf = 0;
	while (in_buf < count) {
		ut64 offset_in_data = offset - rebase_info->start_of_data;
		ut64 page_index = offset_in_data / rebase_info->page_size;
		ut64 page_offset = offset_in_data % rebase_info->page_size;
		ut64 to_next_page = rebase_info->page_size - page_offset;

		if (page_index >= rebase_info->page_starts_count) {
			goto next_page;
		}
		ut64 delta = rebase_info->page_starts[page_index];

		if (delta == DYLD_CACHE_SLIDE_V3_PAGE_ATTR_NO_REBASE) {
			goto next_page;
		}

		ut64 first_rebase_off = delta;
		if (first_rebase_off >= page_offset && first_rebase_off < page_offset + count) {
			do {
				ut64 position = in_buf + first_rebase_off - page_offset;
				if (position >= count) {
					break;
				}
				ut64 raw_value = r_read_le64 (buf + position);
				delta = ((raw_value & rebase_info->delta_mask) >> rebase_info->delta_shift);
				if (position >= start_of_write) {
					ut64 new_value = 0;
					if (R_IS_PTR_AUTHENTICATED (raw_value)) {
						new_value = (raw_value & 0xFFFFFFFFULL) + rebase_info->auth_value_add;
						// TODO: don't throw auth info away
					} else {
						new_value = ((raw_value << 13) & 0xFF00000000000000ULL) | (raw_value & 0x7ffffffffffULL);
						new_value &= 0x00FFFFFFFFFFFFFFULL;
					}
					if (new_value != 0) {
						new_value += rebase_info->slide;
					}
					r_write_le64 (buf + position, new_value);
				}
				first_rebase_off += delta;
			} while (delta);
		}
next_page:
		in_buf += to_next_page;
		offset += to_next_page;
	}
}