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
typedef  int ut8 ;
typedef  int ut64 ;
struct TYPE_3__ {int start_of_data; int page_size; int entries_size; int toc_count; int* entries; size_t* toc; scalar_t__ slide; } ;
typedef  TYPE_1__ RDyldRebaseInfo1 ;

/* Variables and functions */
 int r_read_le64 (int*) ; 
 int /*<<< orphan*/  r_write_le64 (int*,int) ; 

__attribute__((used)) static void rebase_bytes_v1(RDyldRebaseInfo1 *rebase_info, ut8 *buf, ut64 offset, int count, ut64 start_of_write) {
	int in_buf = 0;
	while (in_buf < count) {
		ut64 offset_in_data = offset - rebase_info->start_of_data;
		ut64 page_index = offset_in_data / rebase_info->page_size;
		ut64 page_offset = offset_in_data % rebase_info->page_size;
		ut64 to_next_page = rebase_info->page_size - page_offset;
		ut64 entry_index = page_offset / 32;
		ut64 offset_in_entry = (page_offset % 32) / 4;

		if (entry_index >= rebase_info->entries_size) {
			in_buf += to_next_page;
			offset += to_next_page;
			continue;
		}

		if (page_index >= rebase_info->toc_count) {
			break;
		}

		ut8 *entry = &rebase_info->entries[rebase_info->toc[page_index] * rebase_info->entries_size];
		ut8 b = entry[entry_index];

		if (b & (1 << offset_in_entry)) {
			ut64 value = r_read_le64 (buf + in_buf);
			value += rebase_info->slide;
			r_write_le64 (buf + in_buf, value);
			in_buf += 8;
			offset += 8;
		} else {
			in_buf += 4;
			offset += 4;
		}
	}
}