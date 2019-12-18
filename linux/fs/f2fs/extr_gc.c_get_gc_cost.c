#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct victim_sel_policy {scalar_t__ alloc_mode; scalar_t__ gc_mode; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {unsigned int ckpt_valid_blocks; } ;

/* Variables and functions */
 scalar_t__ GC_GREEDY ; 
 scalar_t__ SSR ; 
 unsigned int get_cb_cost (struct f2fs_sb_info*,unsigned int) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 
 unsigned int get_valid_blocks (struct f2fs_sb_info*,unsigned int,int) ; 

__attribute__((used)) static inline unsigned int get_gc_cost(struct f2fs_sb_info *sbi,
			unsigned int segno, struct victim_sel_policy *p)
{
	if (p->alloc_mode == SSR)
		return get_seg_entry(sbi, segno)->ckpt_valid_blocks;

	/* alloc_mode == LFS */
	if (p->gc_mode == GC_GREEDY)
		return get_valid_blocks(sbi, segno, true);
	else
		return get_cb_cost(sbi, segno);
}