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

void rtw_udelay_os(int us)
{

#ifdef PLATFORM_LINUX

      udelay((unsigned long)us); 

#endif	
#ifdef PLATFORM_FREEBSD
	//Delay for delay microseconds 
	DELAY(us);
	return ;
#endif		
#ifdef PLATFORM_WINDOWS

	NdisStallExecution(us); //(us)

#endif

}