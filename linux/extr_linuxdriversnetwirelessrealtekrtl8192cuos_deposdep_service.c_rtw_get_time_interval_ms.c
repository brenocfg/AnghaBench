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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */

inline s32 rtw_get_time_interval_ms(u32 start, u32 end)
{
#ifdef PLATFORM_LINUX
	return rtw_systime_to_ms(end-start);
#endif
#ifdef PLATFORM_FREEBSD
	return rtw_systime_to_ms(rtw_get_current_time());
#endif	
#ifdef PLATFORM_WINDOWS
	return rtw_systime_to_ms(end-start);
#endif
}