#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  interruptTimerTicks; int /*<<< orphan*/  interruptTimerCPUTicks; int /*<<< orphan*/  isStarted; } ;
struct TYPE_4__ {TYPE_1__ setupData; } ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* pwm2_get_module_data () ; 

__attribute__((used)) static int lpwm2_get_timer_data(lua_State *L) {
  lua_pushboolean(L, pwm2_get_module_data()->setupData.isStarted);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.interruptTimerCPUTicks);
  lua_pushinteger(L, pwm2_get_module_data()->setupData.interruptTimerTicks);
  return 3;
}