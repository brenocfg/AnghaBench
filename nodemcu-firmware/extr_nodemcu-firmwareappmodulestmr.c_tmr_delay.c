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
typedef  int sint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_delay_us (int) ; 
 int /*<<< orphan*/  system_soft_wdt_feed () ; 

__attribute__((used)) static int tmr_delay( lua_State* L ){
	sint32_t us = luaL_checkinteger(L, 1);
	if(us <= 0)
		return luaL_error(L, "wrong arg range");
	while(us >= 1000000){
		us -= 1000000;
		os_delay_us(1000000);
		system_soft_wdt_feed ();
	}
	if(us>0){
		os_delay_us(us);
		system_soft_wdt_feed ();
	}
	return 0;
}