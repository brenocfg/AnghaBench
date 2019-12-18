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
 int /*<<< orphan*/  rtc_timer_update (int) ; 
 scalar_t__ soft_watchdog ; 
 int /*<<< orphan*/  system_restart () ; 

void rtc_callback(void *arg){
	rtc_timer_update(true);
	if(soft_watchdog > 0){
		soft_watchdog--;
		if(soft_watchdog == 0)
			system_restart();
	}
}