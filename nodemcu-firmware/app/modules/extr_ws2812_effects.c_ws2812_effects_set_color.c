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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {void** color; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBRARY_NOT_INITIALIZED_ERROR_MSG ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 void* luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* state ; 

__attribute__((used)) static int ws2812_effects_set_color(lua_State* L) {
  luaL_argcheck(L, state != NULL, 1, LIBRARY_NOT_INITIALIZED_ERROR_MSG);

  uint8_t g = luaL_checkinteger(L, 1);
  uint8_t r = luaL_checkinteger(L, 2);
  uint8_t b = luaL_checkinteger(L, 3);
  uint8_t w = luaL_optinteger(L, 4, 0 );

  state->color[0] = g;
  state->color[1] = r;
  state->color[2] = b;
  state->color[3] = w;
  return 0;
}