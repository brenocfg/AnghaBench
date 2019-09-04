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
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 int /*<<< orphan*/  http_callback ; 
 scalar_t__ http_callback_registry ; 
 int /*<<< orphan*/  http_post (char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int http_lapi_post( lua_State *L )
{
  int length;
  const char * url     = luaL_checklstring(L, 1, &length);
  const char * headers = NULL;
  const char * body    = NULL;

  // Check parameter
  if ((url == NULL))
  {
    return luaL_error( L, "wrong arg type" );
  }

  if (lua_isstring(L, 2))
  {
    headers = luaL_checklstring(L, 2, &length);
  }
  if (lua_isstring(L, 3))
  {
    body = luaL_checklstring(L, 3, &length);
  }

  if (lua_type(L, 4) == LUA_TFUNCTION || lua_type(L, 4) == LUA_TLIGHTFUNCTION) {
    lua_pushvalue(L, 4);  // copy argument (func) to the top of stack
    if (http_callback_registry != LUA_NOREF)
      luaL_unref(L, LUA_REGISTRYINDEX, http_callback_registry);
    http_callback_registry = luaL_ref(L, LUA_REGISTRYINDEX);
  }

  http_post(url, headers, body, http_callback);
  return 0;
}