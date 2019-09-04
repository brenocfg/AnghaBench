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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

u32	rtw_get_current_time(void)
{
	
#ifdef PLATFORM_LINUX
	return jiffies;
#endif	
#ifdef PLATFORM_FREEBSD
	struct timeval tvp;
	getmicrotime(&tvp);
	return tvp.tv_sec;
#endif
#ifdef PLATFORM_WINDOWS
	LARGE_INTEGER	SystemTime;
	NdisGetCurrentSystemTime(&SystemTime);
	return (u32)(SystemTime.LowPart);// count of 100-nanosecond intervals 
#endif
}