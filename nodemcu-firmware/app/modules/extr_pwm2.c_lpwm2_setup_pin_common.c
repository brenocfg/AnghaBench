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
 int const GPIO_PIN_NUM ; 
 int /*<<< orphan*/  luaL_argcheck2 (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pwm2_is_started () ; 
 int /*<<< orphan*/  pwm2_setup_pin (int const,int const,int const,int const,int const) ; 

__attribute__((used)) static int lpwm2_setup_pin_common(lua_State *L, const bool isFreqHz) {
  if (pwm2_is_started()) {
    return luaL_error(L, "pwm2 : already started, stop it before setting up pins.");
  }
  const int pin = lua_tointeger(L, 1);
  const int freq = lua_tointeger(L, 2);
  const int resolution = lua_tointeger(L, 3);
  const int initDuty = lua_tointeger(L, 4);
  const int freqFractions = luaL_optinteger(L, 5, 1);

  luaL_argcheck2(L, pin > 0 && pin <= GPIO_PIN_NUM, 1, "invalid pin number");
  luaL_argcheck2(L, freq > 0, 2, "invalid frequency");
  luaL_argcheck2(L, resolution > 0, 3, "invalid frequency resolution");
  luaL_argcheck2(L, initDuty >= 0 && initDuty <= resolution, 4, "invalid duty");
  luaL_argcheck2(L, freqFractions > 0, 5, "invalid frequency fractions");

  if (isFreqHz) {
    pwm2_setup_pin(pin, freqFractions, freq, resolution, initDuty);
  } else {
    pwm2_setup_pin(pin, freq, freqFractions, resolution, initDuty);
  }
  return 0;
}