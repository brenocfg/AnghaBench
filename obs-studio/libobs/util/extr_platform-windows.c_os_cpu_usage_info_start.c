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
struct TYPE_8__ {int /*<<< orphan*/  ft; } ;
struct TYPE_7__ {int /*<<< orphan*/  ft; } ;
struct TYPE_6__ {int /*<<< orphan*/  ft; } ;
struct os_cpu_usage_info {int /*<<< orphan*/  core_count; TYPE_3__ last_user_time; TYPE_2__ last_sys_time; TYPE_1__ last_time; } ;
typedef  struct os_cpu_usage_info os_cpu_usage_info_t ;
struct TYPE_9__ {int /*<<< orphan*/  dwNumberOfProcessors; } ;
typedef  TYPE_4__ SYSTEM_INFO ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetProcessTimes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 
 struct os_cpu_usage_info* bzalloc (int) ; 

os_cpu_usage_info_t *os_cpu_usage_info_start(void)
{
	struct os_cpu_usage_info *info = bzalloc(sizeof(*info));
	SYSTEM_INFO si;
	FILETIME dummy;

	GetSystemInfo(&si);
	GetSystemTimeAsFileTime(&info->last_time.ft);
	GetProcessTimes(GetCurrentProcess(), &dummy, &dummy,
			&info->last_sys_time.ft, &info->last_user_time.ft);
	info->core_count = si.dwNumberOfProcessors;

	return info;
}