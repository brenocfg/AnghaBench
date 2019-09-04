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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */

u64 rtw_division64(u64 x, u64 y)
{
#ifdef PLATFORM_LINUX
	do_div(x, y);
	return x;
#elif defined(PLATFORM_WINDOWS)
	return (x / y);
#elif defined(PLATFORM_FREEBSD)
	return (x / y);
#endif
}