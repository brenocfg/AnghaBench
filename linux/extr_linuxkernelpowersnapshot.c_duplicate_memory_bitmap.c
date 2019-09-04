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
 unsigned long memory_bm_next_pfn (struct memory_bitmap*) ; 
 int /*<<< orphan*/  memory_bm_position_reset (struct memory_bitmap*) ; 
 int /*<<< orphan*/  memory_bm_set_bit (struct memory_bitmap*,unsigned long) ; 

__attribute__((used)) static void duplicate_memory_bitmap(struct memory_bitmap *dst,
				    struct memory_bitmap *src)
{
	unsigned long pfn;

	memory_bm_position_reset(src);
	pfn = memory_bm_next_pfn(src);
	while (pfn != BM_END_OF_MAP) {
		memory_bm_set_bit(dst, pfn);
		pfn = memory_bm_next_pfn(src);
	}
}