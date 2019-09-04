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

inline u32 rtw_systime_to_ms(u32 systime)
{
#ifdef PLATFORM_LINUX
	return systime * 1000 / HZ;
#endif	
#ifdef PLATFORM_FREEBSD
	return systime * 1000;
#endif	
#ifdef PLATFORM_WINDOWS
	return systime / 10000 ; 
#endif
}