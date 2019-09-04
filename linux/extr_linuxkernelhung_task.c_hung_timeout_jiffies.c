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
 unsigned long HZ ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 unsigned long jiffies ; 

__attribute__((used)) static long hung_timeout_jiffies(unsigned long last_checked,
				 unsigned long timeout)
{
	/* timeout of 0 will disable the watchdog */
	return timeout ? last_checked - jiffies + timeout * HZ :
		MAX_SCHEDULE_TIMEOUT;
}