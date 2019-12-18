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
struct f2fs_sb_info {unsigned long* last_time; } ;

/* Variables and functions */
 size_t DISCARD_TIME ; 
 size_t GC_TIME ; 
 int REQ_TIME ; 
 unsigned long jiffies ; 

__attribute__((used)) static inline void f2fs_update_time(struct f2fs_sb_info *sbi, int type)
{
	unsigned long now = jiffies;

	sbi->last_time[type] = now;

	/* DISCARD_TIME and GC_TIME are based on REQ_TIME */
	if (type == REQ_TIME) {
		sbi->last_time[DISCARD_TIME] = now;
		sbi->last_time[GC_TIME] = now;
	}
}