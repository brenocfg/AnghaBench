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
typedef  int /*<<< orphan*/  _sema ;

/* Variables and functions */

u32 _rtw_down_sema(_sema *sema)
{

#ifdef PLATFORM_LINUX
	
	if (down_interruptible(sema))
		return _FAIL;
	else
		return _SUCCESS;

#endif    	
#ifdef PLATFORM_FREEBSD
	sema_wait(sema);
	return  _SUCCESS;
#endif
#ifdef PLATFORM_OS_XP

	if(STATUS_SUCCESS == KeWaitForSingleObject(sema, Executive, KernelMode, TRUE, NULL))
		return  _SUCCESS;
	else
		return _FAIL;
#endif

#ifdef PLATFORM_OS_CE
	if(WAIT_OBJECT_0 == WaitForSingleObject(*sema, INFINITE ))
		return _SUCCESS; 
	else
		return _FAIL;
#endif
}