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
typedef  int /*<<< orphan*/  _sema ;

/* Variables and functions */

void _rtw_up_sema(_sema	*sema)
{

#ifdef PLATFORM_LINUX

	up(sema);

#endif	
#ifdef PLATFORM_FREEBSD
	sema_post(sema);
#endif
#ifdef PLATFORM_OS_XP

	KeReleaseSemaphore(sema, IO_NETWORK_INCREMENT, 1,  FALSE );

#endif

#ifdef PLATFORM_OS_CE
	ReleaseSemaphore(*sema,  1,  NULL );
#endif
}