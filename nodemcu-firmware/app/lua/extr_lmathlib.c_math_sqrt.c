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
typedef  scalar_t__ lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  isqrt (scalar_t__) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqrt (scalar_t__) ; 

__attribute__((used)) static int math_sqrt (lua_State *L) {
#ifdef LUA_NUMBER_INTEGRAL
  lua_Number x = luaL_checknumber(L, 1);
  luaL_argcheck(L, 0<=x, 1, "negative");
  lua_pushnumber(L, isqrt(x));
#else
  lua_pushnumber(L, sqrt(luaL_checknumber(L, 1)));
#endif
  return 1;
}