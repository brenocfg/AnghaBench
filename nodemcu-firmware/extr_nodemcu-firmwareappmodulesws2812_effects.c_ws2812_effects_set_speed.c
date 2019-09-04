#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int speed; int mode_delay; } ;

/* Variables and functions */
 char* LIBRARY_NOT_INITIALIZED_ERROR_MSG ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* state ; 

__attribute__((used)) static int ws2812_effects_set_speed(lua_State* L) {
  uint8_t speed = luaL_checkinteger(L, 1);
  luaL_argcheck(L, state != NULL, 1, LIBRARY_NOT_INITIALIZED_ERROR_MSG);
  luaL_argcheck(L, speed >= 0 && speed <= 255, 1, "should be a 0-255");
  state->speed = speed;
  state->mode_delay = 10;
  return 0;
}