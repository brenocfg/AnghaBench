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
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 int TOTAL_SEGS (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 

__attribute__((used)) static inline void check_seg_range(struct f2fs_sb_info *sbi, unsigned int segno)
{
	f2fs_bug_on(sbi, segno > TOTAL_SEGS(sbi) - 1);
}