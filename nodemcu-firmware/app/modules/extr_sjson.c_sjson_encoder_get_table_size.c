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
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sjson_encoder_get_table_size(lua_State *L, int argno) {
  // Returns -1 for object, otherwise the maximum integer key value found.
  lua_pushvalue(L, argno);
  // stack now contains: -1 => table
  lua_pushnil(L);
  // stack now contains: -1 => nil; -2 => table
  //
  int maxkey = 0;

  while (lua_next(L, -2)) {
    lua_pop(L, 1);
    // stack now contains: -1 => key; -2 => table
    if (lua_type(L, -1) == LUA_TNUMBER) {
      int val = lua_tointeger(L, -1);
      if (val > maxkey) {
        maxkey = val;
      } else if (val <= 0) {
        maxkey = -1;
        lua_pop(L, 1);
        break;
      }
    } else {
      maxkey = -1;
      lua_pop(L, 1);
      break;
    }
  }

  lua_pop(L, 1);

  return maxkey;
}