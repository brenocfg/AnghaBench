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
struct f2fs_sb_info {unsigned long* interval_time; scalar_t__* last_time; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool f2fs_time_over(struct f2fs_sb_info *sbi, int type)
{
	unsigned long interval = sbi->interval_time[type] * HZ;

	return time_after(jiffies, sbi->last_time[type] + interval);
}