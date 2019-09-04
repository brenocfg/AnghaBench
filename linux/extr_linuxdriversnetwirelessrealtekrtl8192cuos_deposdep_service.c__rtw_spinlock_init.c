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
typedef  int /*<<< orphan*/  _lock ;

/* Variables and functions */

void	_rtw_spinlock_init(_lock *plock)
{

#ifdef PLATFORM_LINUX

	spin_lock_init(plock);

#endif	
#ifdef PLATFORM_FREEBSD
		mtx_init(plock, "", NULL, MTX_DEF|MTX_RECURSE);
#endif
#ifdef PLATFORM_WINDOWS

	NdisAllocateSpinLock(plock);

#endif
	
}