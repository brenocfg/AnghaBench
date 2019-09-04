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

inline u32 rtw_ms_to_systime(u32 ms)
{
#ifdef PLATFORM_LINUX
	return ms * HZ / 1000;
#endif	
#ifdef PLATFORM_FREEBSD
	return ms /1000;
#endif	
#ifdef PLATFORM_WINDOWS
	return ms * 10000 ; 
#endif
}