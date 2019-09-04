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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBRARY_NOT_INITIALIZED_ERROR_MSG ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* state ; 

__attribute__((used)) static int ws2812_effects_get_speed(lua_State* L) {
  luaL_argcheck(L, state != NULL, 1, LIBRARY_NOT_INITIALIZED_ERROR_MSG);
  lua_pushnumber(L, state->speed);
  return 1;
}