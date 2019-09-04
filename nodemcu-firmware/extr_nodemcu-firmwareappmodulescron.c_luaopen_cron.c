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
 int /*<<< orphan*/  SWTIMER_RESTART ; 
 int /*<<< orphan*/  cron_handle_tmr ; 
 int /*<<< orphan*/  cron_timer ; 
 scalar_t__ cronent_map ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int luaopen_cron( lua_State *L ) {
  os_timer_disarm(&cron_timer);
  os_timer_setfn(&cron_timer, cron_handle_tmr, 0);
  SWTIMER_REG_CB(cron_handle_tmr, SWTIMER_RESTART);
    //cron_handle_tmr determines when to execute a scheduled cron job
    //My guess: To be sure to give the other modules required by cron enough time to get to a ready state, restart cron_timer.
  os_timer_arm(&cron_timer, 1000, 0);
  luaL_rometatable(L, "cron.entry", (void *)cronent_map);
  return 0;
}