#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* pin; } ;
struct TYPE_6__ {TYPE_2__ setupData; } ;
struct TYPE_4__ {int /*<<< orphan*/  resolutionInterruptCounterMultiplier; int /*<<< orphan*/  resolutionCPUTicks; int /*<<< orphan*/  frequencyDivisor; int /*<<< orphan*/  divisableFrequency; int /*<<< orphan*/  pulseResolutions; int /*<<< orphan*/  duty; } ;

/* Variables and functions */
 size_t const GPIO_PIN_NUM ; 
 int /*<<< orphan*/  luaL_argcheck2 (int /*<<< orphan*/ *,int,int,char*) ; 
 size_t luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* pwm2_get_module_data () ; 
 int /*<<< orphan*/  pwm2_is_pin_setup (size_t const) ; 

__attribute__((used)) static int lpwm2_get_pin_data(lua_State *L) {
  const uint8 pin = luaL_checkinteger(L, 1);
  luaL_argcheck2(L, pin > 0 && pin <= GPIO_PIN_NUM, 1, "invalid pin number");
  lua_pushinteger(L, pwm2_is_pin_setup(pin));
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].duty);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].pulseResolutions);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].divisableFrequency);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].frequencyDivisor);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].resolutionCPUTicks);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.pin[pin].resolutionInterruptCounterMultiplier);
  return 7;
}