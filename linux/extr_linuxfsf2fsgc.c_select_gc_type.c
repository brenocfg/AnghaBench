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
struct f2fs_sb_info {int gc_mode; } ;

/* Variables and functions */
 int BG_GC ; 
 int GC_CB ; 
 int GC_GREEDY ; 
#define  GC_IDLE_CB 130 
#define  GC_IDLE_GREEDY 129 
#define  GC_URGENT 128 

__attribute__((used)) static int select_gc_type(struct f2fs_sb_info *sbi, int gc_type)
{
	int gc_mode = (gc_type == BG_GC) ? GC_CB : GC_GREEDY;

	switch (sbi->gc_mode) {
	case GC_IDLE_CB:
		gc_mode = GC_CB;
		break;
	case GC_IDLE_GREEDY:
	case GC_URGENT:
		gc_mode = GC_GREEDY;
		break;
	}
	return gc_mode;
}