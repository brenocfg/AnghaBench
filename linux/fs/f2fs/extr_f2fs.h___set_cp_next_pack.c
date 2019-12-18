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
struct f2fs_sb_info {int cur_cp_pack; } ;

/* Variables and functions */

__attribute__((used)) static inline void __set_cp_next_pack(struct f2fs_sb_info *sbi)
{
	sbi->cur_cp_pack = (sbi->cur_cp_pack == 1) ? 2 : 1;
}