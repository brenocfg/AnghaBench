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
 int /*<<< orphan*/  LUA_INIT ; 
 char* LUA_INIT_STRING ; 
 int dofsfile (int /*<<< orphan*/ *,char const*) ; 
 int dostring (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_luainit (lua_State *L) {
  const char *init = LUA_INIT_STRING;
  if (init[0] == '@')
    return dofsfile(L, init+1);
  else
    return dostring(L, init, LUA_INIT);
}