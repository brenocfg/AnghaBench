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

void rtw_msleep_os(int ms)
{

#ifdef PLATFORM_LINUX

  	msleep((unsigned int)ms);

#endif	
#ifdef PLATFORM_FREEBSD
       //Delay for delay microseconds 
	DELAY(ms*1000);
	return ;
#endif	
#ifdef PLATFORM_WINDOWS

	NdisMSleep(ms*1000); //(us)*1000=(ms)

#endif


}