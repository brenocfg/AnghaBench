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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* pin; } ;
struct TYPE_6__ {TYPE_2__ setupData; } ;
struct TYPE_4__ {int pulseResolutions; } ;

/* Variables and functions */
 int GPIO_PIN_NUM ; 
 int /*<<< orphan*/  luaL_argcheck2 (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 TYPE_3__* pwm2_get_module_data () ; 
 int /*<<< orphan*/  pwm2_is_pin_setup (int) ; 
 int /*<<< orphan*/  pwm2_set_duty (int,int) ; 

__attribute__((used)) static int lpwm2_set_duty(lua_State *L) {
  int pos = 0;
  while (true) {
    int pin = luaL_optinteger(L, ++pos, -1);
    if (pin == -1) {
      break;
    }
    luaL_argcheck2(L, pin > 0 && pin <= GPIO_PIN_NUM, pos, "invalid pin number");

    int duty = luaL_optinteger(L, ++pos, -1);
    luaL_argcheck2(L, duty >= 0 && duty <= pwm2_get_module_data()->setupData.pin[pin].pulseResolutions, pos, "invalid duty");

    if (!pwm2_is_pin_setup(pin)) {
      return luaL_error(L, "pwm2 : pin=%d is not setup yet", pin);
    }
    pwm2_set_duty(pin, duty);
  }
  return 0;
}