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
 scalar_t__ NULL_MODE ; 
 int /*<<< orphan*/  wifi_fpm_auto_sleep_set_in_null_mode (int) ; 
 scalar_t__ wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_opmode_current (scalar_t__) ; 

int luaopen_wifi( lua_State *L )
{
  wifi_fpm_auto_sleep_set_in_null_mode(1);
  //if esp is already in NULL_MODE, auto sleep setting won't take effect until next wifi_set_opmode(NULL_MODE) call.
  if(wifi_get_opmode()==NULL_MODE)
  {
    wifi_set_opmode_current(NULL_MODE);
  }
#if defined(WIFI_SDK_EVENT_MONITOR_ENABLE)
  wifi_eventmon_init();
#endif
#if defined(LUA_USE_MODULES_WIFI_MONITOR)
  wifi_monitor_init(L);
#endif
 return 0;
}