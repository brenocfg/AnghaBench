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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_mask_ok (int /*<<< orphan*/ ) ; 
 size_t hash_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpageflags_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nr_pages ; 
 scalar_t__ opt_cgroup ; 
 int opt_list ; 
 int /*<<< orphan*/  pagemap_swap_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_page (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_page_range (unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_pages ; 

__attribute__((used)) static void walk_swap(unsigned long voffset, uint64_t pme)
{
	uint64_t flags = kpageflags_flags(0, pme);

	if (!bit_mask_ok(flags))
		return;

	if (opt_cgroup)
		return;

	if (opt_list == 1)
		show_page_range(voffset, pagemap_swap_offset(pme),
				1, flags, 0, 0);
	else if (opt_list == 2)
		show_page(voffset, pagemap_swap_offset(pme), flags, 0, 0);

	nr_pages[hash_slot(flags)]++;
	total_pages++;
}