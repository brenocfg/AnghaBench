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
 int GPIO_PIN_NUM ; 
 int /*<<< orphan*/  luaL_argcheck2 (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ pwm2_is_started () ; 
 int /*<<< orphan*/  pwm2_release_pin (int) ; 

__attribute__((used)) static int lpwm2_release_pin(lua_State *L) {
  if (pwm2_is_started()) {
    return luaL_error(L, "pwm2 : pwm is started, stop it first.");
  }
  int pos = 0;
  while (true) {
    int pin = luaL_optinteger(L, ++pos, -1);
    if (pin == -1) {
      break;
    }
    luaL_argcheck2(L, pin > 0 && pin <= GPIO_PIN_NUM, pos, "invalid pin number");
    pwm2_release_pin(2);
  }
  return 0;
}