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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_PULLUP ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int* pin_num ; 
 int /*<<< orphan*/  platform_gpio_exists (size_t) ; 
 int /*<<< orphan*/  platform_gpio_mode (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switec ; 
 scalar_t__ switec_close (unsigned int) ; 
 scalar_t__ switec_setup (unsigned int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

__attribute__((used)) static int lswitec_setup( lua_State* L )
{
  unsigned int id;

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( switec, id );
  int pin[4];

  if (switec_close(id)) {
    return luaL_error( L, "Unable to setup stepper." );
  }

  int i;
  for (i = 0; i < 4; i++) {
    uint32_t gpio = luaL_checkinteger(L, 2 + i);

    luaL_argcheck(L, platform_gpio_exists(gpio), 2 + i, "Invalid pin");

    pin[i] = pin_num[gpio];

    platform_gpio_mode(gpio, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_PULLUP);
  }

  int deg_per_sec = 0;
  if (lua_gettop(L) >= 6) {
    deg_per_sec = luaL_checkinteger(L, 6);
  }

  if (switec_setup(id, pin, deg_per_sec, tasknumber)) {
    return luaL_error(L, "Unable to setup stepper.");
  }
  return 0;
}