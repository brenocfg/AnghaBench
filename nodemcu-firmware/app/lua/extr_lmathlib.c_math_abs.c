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
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int math_abs (lua_State *L) {
#ifdef LUA_NUMBER_INTEGRAL
  lua_Number x = luaL_checknumber(L, 1);
  if (x < 0) x = -x;	//fails for -2^31
  lua_pushnumber(L, x);
#else
  lua_pushnumber(L, fabs(luaL_checknumber(L, 1)));
#endif
  return 1;
}