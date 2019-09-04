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

/* Variables and functions */

void rtw_sleep_schedulable(int ms)	
{

#ifdef PLATFORM_LINUX

    u32 delta;
    
    delta = (ms * HZ)/1000;//(ms)
    if (delta == 0) {
        delta = 1;// 1 ms
    }
    set_current_state(TASK_INTERRUPTIBLE);
    if (schedule_timeout(delta) != 0) {
        return ;
    }
    return;

#endif	
#ifdef PLATFORM_FREEBSD
	DELAY(ms*1000);
	return ;
#endif	
	
#ifdef PLATFORM_WINDOWS

	NdisMSleep(ms*1000); //(us)*1000=(ms)

#endif

}