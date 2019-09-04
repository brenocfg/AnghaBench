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
typedef  int /*<<< orphan*/  pulse_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  TIMER_OWNER ; 
 int /*<<< orphan*/ * active_pulser ; 
 int active_pulser_ref ; 
 int gpio_pulse_push_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_hw_timer_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_pulse_cancel(lua_State *L) {
  pulse_t *pulser = luaL_checkudata(L, 1, "gpio.pulse");

  if (active_pulser != pulser) {
    return 0;
  }

  // Shut off the timer
  platform_hw_timer_close(TIMER_OWNER);

  int rc = gpio_pulse_push_state(L, active_pulser);

  active_pulser = NULL;

  int pulser_ref = active_pulser_ref;
  active_pulser_ref = LUA_NOREF;
  luaL_unref(L, LUA_REGISTRYINDEX, pulser_ref);

  return rc;
}