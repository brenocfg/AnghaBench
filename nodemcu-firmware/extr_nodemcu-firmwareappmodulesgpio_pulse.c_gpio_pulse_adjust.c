#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int next_adjust; } ;
typedef  TYPE_1__ pulse_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* active_pulser ; 
 int gpio_pulse_push_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int gpio_pulse_adjust(lua_State *L) {
  pulse_t *pulser = luaL_checkudata(L, 1, "gpio.pulse");

  if (active_pulser != pulser) {
    return 0;
  }

  int offset = luaL_checkinteger(L, 2);
  // This will alter the next adjustable
  pulser->next_adjust = offset;

  int rc = gpio_pulse_push_state(L, active_pulser);

  return rc;
}