#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LROT_TABLEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ fvalue (scalar_t__) ; 
 int /*<<< orphan*/  lua_call (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_islightfunction (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_libs ; 
 scalar_t__ lua_next (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_pushnil (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushrotable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (TYPE_1__*,int) ; 

void luaL_openlibs (lua_State *L) {

  lua_pushrotable(L, LROT_TABLEREF(lua_libs));
  lua_pushnil(L);  /* first key */
  /* loop round and open libraries */
#ifndef LUA_CROSS_COMPILER
// luaL_dbgbreak();  // This is a test point for debugging library start ups
#endif
  while (lua_next(L, -2) != 0) {
    if (lua_islightfunction(L,-1) &&
        fvalue(L->top-1)) { // only process function entries
      lua_pushvalue(L, -2);
      lua_call(L, 1, 0);  // call luaopen_XXX(libname)
    } else {
      lua_pop(L, 1);
    }
  }
  lua_pop(L, 1);  //cleanup stack
}