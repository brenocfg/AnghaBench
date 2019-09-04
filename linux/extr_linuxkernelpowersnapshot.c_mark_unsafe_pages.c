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
struct memory_bitmap {int dummy; } ;

/* Variables and functions */
 unsigned long BM_END_OF_MAP ; 
 scalar_t__ allocated_unsafe_pages ; 
 int /*<<< orphan*/  duplicate_memory_bitmap (int /*<<< orphan*/ ,struct memory_bitmap*) ; 
 int /*<<< orphan*/  free_pages_map ; 
 int /*<<< orphan*/  memory_bm_clear_current (int /*<<< orphan*/ ) ; 
 unsigned long memory_bm_next_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_unsafe_pages(struct memory_bitmap *bm)
{
	unsigned long pfn;

	/* Clear the "free"/"unsafe" bit for all PFNs */
	memory_bm_position_reset(free_pages_map);
	pfn = memory_bm_next_pfn(free_pages_map);
	while (pfn != BM_END_OF_MAP) {
		memory_bm_clear_current(free_pages_map);
		pfn = memory_bm_next_pfn(free_pages_map);
	}

	/* Mark pages that correspond to the "original" PFNs as "unsafe" */
	duplicate_memory_bitmap(free_pages_map, bm);

	allocated_unsafe_pages = 0;
}