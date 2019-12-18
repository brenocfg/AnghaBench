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
typedef  int time64_t ;
typedef  int time32_t ;
struct timezone {int tz_minuteswest; } ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int sb_timeshift; } ;

/* Variables and functions */
 TYPE_1__* hpfs_sb (struct super_block*) ; 

__attribute__((used)) static inline time32_t gmt_to_local(struct super_block *s, time64_t t)
{
	extern struct timezone sys_tz;
	return t - sys_tz.tz_minuteswest * 60 - hpfs_sb(s)->sb_timeshift;
}