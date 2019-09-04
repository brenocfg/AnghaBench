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
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 scalar_t__ ws2812_buffer_map ; 

int luaopen_ws2812(lua_State *L) {
  // TODO: Make sure that the GPIO system is initialized
  luaL_rometatable(L, "ws2812.buffer", (void *)ws2812_buffer_map);  // create metatable for ws2812.buffer
  return 0;
}