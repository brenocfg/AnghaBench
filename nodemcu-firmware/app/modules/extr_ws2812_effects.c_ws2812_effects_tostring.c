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
typedef  int /*<<< orphan*/  luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  luaL_addstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ws2812_effects_tostring(lua_State* L) {

  luaL_Buffer result;
  luaL_buffinit(L, &result);

  luaL_addchar(&result, '[');
  luaL_addstring(&result, "effects");
  luaL_addchar(&result, ']');
  luaL_pushresult(&result);

  return 1;
}