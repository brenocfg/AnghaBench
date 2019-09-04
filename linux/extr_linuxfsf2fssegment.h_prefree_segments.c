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
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {unsigned int* nr_dirty; } ;

/* Variables and functions */
 TYPE_1__* DIRTY_I (struct f2fs_sb_info*) ; 
 size_t PRE ; 

__attribute__((used)) static inline unsigned int prefree_segments(struct f2fs_sb_info *sbi)
{
	return DIRTY_I(sbi)->nr_dirty[PRE];
}