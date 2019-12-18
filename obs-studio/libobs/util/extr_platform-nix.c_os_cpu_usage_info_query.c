#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tms {scalar_t__ tms_stime; scalar_t__ tms_utime; } ;
struct TYPE_3__ {scalar_t__ last_cpu_time; scalar_t__ last_sys_time; scalar_t__ last_user_time; scalar_t__ core_count; } ;
typedef  TYPE_1__ os_cpu_usage_info_t ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 scalar_t__ times (struct tms*) ; 

double os_cpu_usage_info_query(os_cpu_usage_info_t *info)
{
	struct tms time_sample;
	clock_t cur_cpu_time;
	double percent;

	if (!info)
		return 0.0;

	cur_cpu_time = times(&time_sample);
	if (cur_cpu_time <= info->last_cpu_time ||
	    time_sample.tms_stime < info->last_sys_time ||
	    time_sample.tms_utime < info->last_user_time)
		return 0.0;

	percent = (double)(time_sample.tms_stime - info->last_sys_time +
			   (time_sample.tms_utime - info->last_user_time));
	percent /= (double)(cur_cpu_time - info->last_cpu_time);
	percent /= (double)info->core_count;

	info->last_cpu_time = cur_cpu_time;
	info->last_sys_time = time_sample.tms_stime;
	info->last_user_time = time_sample.tms_utime;

	return percent * 100.0;
}