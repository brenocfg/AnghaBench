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
struct victim_sel_policy {scalar_t__ alloc_mode; scalar_t__ gc_mode; int ofs_unit; } ;
struct f2fs_sb_info {unsigned int blocks_per_seg; } ;

/* Variables and functions */
 scalar_t__ GC_CB ; 
 scalar_t__ GC_GREEDY ; 
 scalar_t__ SSR ; 
 unsigned int UINT_MAX ; 

__attribute__((used)) static unsigned int get_max_cost(struct f2fs_sb_info *sbi,
				struct victim_sel_policy *p)
{
	/* SSR allocates in a segment unit */
	if (p->alloc_mode == SSR)
		return sbi->blocks_per_seg;
	if (p->gc_mode == GC_GREEDY)
		return 2 * sbi->blocks_per_seg * p->ofs_unit;
	else if (p->gc_mode == GC_CB)
		return UINT_MAX;
	else /* No other gc_mode */
		return 0;
}