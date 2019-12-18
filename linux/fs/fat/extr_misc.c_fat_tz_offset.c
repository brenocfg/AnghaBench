#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int time_offset; scalar_t__ tz_set; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
struct TYPE_4__ {int tz_minuteswest; } ;

/* Variables and functions */
 int SECS_PER_MIN ; 
 TYPE_2__ sys_tz ; 

__attribute__((used)) static inline int fat_tz_offset(struct msdos_sb_info *sbi)
{
	return (sbi->options.tz_set ?
	       -sbi->options.time_offset :
	       sys_tz.tz_minuteswest) * SECS_PER_MIN;
}