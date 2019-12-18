#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union time_data {scalar_t__ val; int /*<<< orphan*/  ft; } ;
struct TYPE_8__ {scalar_t__ val; } ;
struct TYPE_7__ {scalar_t__ val; } ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_9__ {TYPE_3__ last_user_time; TYPE_2__ last_sys_time; TYPE_1__ last_time; scalar_t__ core_count; } ;
typedef  TYPE_4__ os_cpu_usage_info_t ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessTimes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 

double os_cpu_usage_info_query(os_cpu_usage_info_t *info)
{
	union time_data cur_time, cur_sys_time, cur_user_time;
	FILETIME dummy;
	double percent;

	if (!info)
		return 0.0;

	GetSystemTimeAsFileTime(&cur_time.ft);
	GetProcessTimes(GetCurrentProcess(), &dummy, &dummy, &cur_sys_time.ft,
			&cur_user_time.ft);

	percent = (double)(cur_sys_time.val - info->last_sys_time.val +
			   (cur_user_time.val - info->last_user_time.val));
	percent /= (double)(cur_time.val - info->last_time.val);
	percent /= (double)info->core_count;

	info->last_time.val = cur_time.val;
	info->last_sys_time.val = cur_sys_time.val;
	info->last_user_time.val = cur_user_time.val;

	return percent * 100.0;
}