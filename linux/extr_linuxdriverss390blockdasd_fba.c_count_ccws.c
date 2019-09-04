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
typedef  unsigned int sector_t ;

/* Variables and functions */

__attribute__((used)) static int count_ccws(sector_t first_rec, sector_t last_rec,
		      unsigned int blocks_per_page)
{
	sector_t wz_stop = 0, d_stop = 0;
	int cur_pos = 0;
	int count = 0;

	if (first_rec % blocks_per_page != 0) {
		wz_stop = first_rec + blocks_per_page -
			(first_rec % blocks_per_page) - 1;
		if (wz_stop > last_rec)
			wz_stop = last_rec;
		cur_pos = wz_stop - first_rec + 1;
		count++;
	}

	if (last_rec - (first_rec + cur_pos) + 1 >= blocks_per_page) {
		if ((last_rec - blocks_per_page + 1) % blocks_per_page != 0)
			d_stop = last_rec - ((last_rec - blocks_per_page + 1) %
					     blocks_per_page);
		else
			d_stop = last_rec;

		cur_pos += d_stop - (first_rec + cur_pos) + 1;
		count++;
	}

	if (cur_pos == 0 || first_rec + cur_pos - 1 < last_rec)
		count++;

	return count;
}