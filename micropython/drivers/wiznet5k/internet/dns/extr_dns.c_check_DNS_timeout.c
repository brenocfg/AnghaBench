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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int int8_t ;

/* Variables and functions */
 int DNS_WAIT_TIME ; 
 int HAL_GetTick () ; 
 scalar_t__ MAX_DNS_RETRY ; 
 int hal_sys_tick ; 

int8_t check_DNS_timeout(void)
{
	static uint8_t retry_count;

    uint32_t tick = HAL_GetTick();
	if(tick - hal_sys_tick >= DNS_WAIT_TIME * 1000)
	{
		hal_sys_tick = tick;
		if(retry_count >= MAX_DNS_RETRY) {
			retry_count = 0;
			return -1; // timeout occurred
		}
		retry_count++;
		return 0; // timer over, but no timeout
	}

	return 1; // no timer over, no timeout occur
}