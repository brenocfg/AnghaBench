#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* tmr_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int mode; scalar_t__ interval; int /*<<< orphan*/  os; } ;

/* Variables and functions */
 scalar_t__ MAX_TIMEOUT ; 
 int /*<<< orphan*/  MAX_TIMEOUT_ERR_STR ; 
 int TIMER_IDLE_FLAG ; 
 int TIMER_MODE_AUTO ; 
 int TIMER_MODE_OFF ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 TYPE_1__* tmr_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tmr_interval(lua_State* L){
	tmr_t tmr = tmr_get(L, 1);

	uint32_t interval = luaL_checkinteger(L, 2);
	luaL_argcheck(L, (interval > 0 && interval <= MAX_TIMEOUT), 2, MAX_TIMEOUT_ERR_STR);
	if(tmr->mode != TIMER_MODE_OFF){
		tmr->interval = interval;
		if(!(tmr->mode&TIMER_IDLE_FLAG)){
			os_timer_disarm(&tmr->os);
			os_timer_arm(&tmr->os, tmr->interval, tmr->mode==TIMER_MODE_AUTO);
		}
	}
	return 0;
}