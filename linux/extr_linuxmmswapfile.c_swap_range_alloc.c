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
struct swap_info_struct {unsigned long lowest_bit; unsigned int highest_bit; scalar_t__ inuse_pages; scalar_t__ pages; unsigned int max; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_from_avail_list (struct swap_info_struct*) ; 

__attribute__((used)) static void swap_range_alloc(struct swap_info_struct *si, unsigned long offset,
			     unsigned int nr_entries)
{
	unsigned int end = offset + nr_entries - 1;

	if (offset == si->lowest_bit)
		si->lowest_bit += nr_entries;
	if (end == si->highest_bit)
		si->highest_bit -= nr_entries;
	si->inuse_pages += nr_entries;
	if (si->inuse_pages == si->pages) {
		si->lowest_bit = si->max;
		si->highest_bit = 0;
		del_from_avail_list(si);
	}
}