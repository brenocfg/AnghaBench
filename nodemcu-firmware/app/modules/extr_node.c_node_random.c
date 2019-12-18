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
typedef  int lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int node_random_range (int,int) ; 
 int /*<<< orphan*/  os_random () ; 

__attribute__((used)) static int node_random (lua_State *L) {
  int u;
  int l;

  switch (lua_gettop(L)) {  /* check number of arguments */
    case 0: {  /* no arguments */
#ifdef LUA_NUMBER_INTEGRAL
      lua_pushnumber(L, 0);  /* Number between 0 and 1 - always 0 with ints */
#else
      lua_pushnumber(L, (lua_Number)os_random() / (lua_Number)(1LL << 32));
#endif
      return 1;
    }
    case 1: {  /* only upper limit */
      l = 1;
      u = luaL_checkint(L, 1);
      break;
    }
    case 2: {  /* lower and upper limits */
      l = luaL_checkint(L, 1);
      u = luaL_checkint(L, 2);
      break;
    }
    default:
      return luaL_error(L, "wrong number of arguments");
  }
  luaL_argcheck(L, l<=u, 2, "interval is empty");
  lua_pushnumber(L, node_random_range(l, u));  /* int between `l' and `u' */
  return 1;
}