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
typedef  int /*<<< orphan*/  _mutex ;

/* Variables and functions */

void	_rtw_mutex_free(_mutex *pmutex)
{
#ifdef PLATFORM_LINUX

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
	mutex_destroy(pmutex);
#else	
#endif

#ifdef PLATFORM_FREEBSD
	sema_destroy(pmutex);
#endif

#endif

#ifdef PLATFORM_OS_XP

#endif

#ifdef PLATFORM_OS_CE

#endif
}