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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SWTIMER_REG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  alarm_timer_common ; 
 int /*<<< orphan*/  last_rtc_time ; 
 scalar_t__ last_rtc_time_us ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_callback ; 
 int /*<<< orphan*/  rtc_timer ; 
 int /*<<< orphan*/  system_get_rtc_time () ; 
 scalar_t__ tmr_dyn_map ; 

int luaopen_tmr( lua_State *L ){
	luaL_rometatable(L, "tmr.timer", (void *)tmr_dyn_map);

	last_rtc_time=system_get_rtc_time(); // Right now is time 0
	last_rtc_time_us=0;

	os_timer_disarm(&rtc_timer);
	os_timer_setfn(&rtc_timer, rtc_callback, NULL);
	os_timer_arm(&rtc_timer, 1000, 1);

  SWTIMER_REG_CB(rtc_callback, SWTIMER_RESUME);
  //The function rtc_callback calls the a function that calibrates the SoftRTC for drift in the esp8266's clock.
  //My guess: after the duration of light_sleep there's bound to be some drift in the clock, so a calibration is due.
  SWTIMER_REG_CB(alarm_timer_common, SWTIMER_RESUME);
  //The function alarm_timer_common handles timers created by the developer via tmr.create().
  //No reason not to resume the timers, so resume em'.


	return 0;
}