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
struct TYPE_2__ {int dirty_nat_cnt; int max_nid; int dirty_nats_ratio; } ;

/* Variables and functions */
 TYPE_1__* NM_I (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline bool excess_dirty_nats(struct f2fs_sb_info *sbi)
{
	return NM_I(sbi)->dirty_nat_cnt >= NM_I(sbi)->max_nid *
					NM_I(sbi)->dirty_nats_ratio / 100;
}