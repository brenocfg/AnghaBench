#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int connectionState; scalar_t__ reservedData; int /*<<< orphan*/  extraHeaders; } ;
typedef  TYPE_1__ ws_info ;
struct TYPE_5__ {scalar_t__ onConnection; scalar_t__ onReceive; scalar_t__ onClose; scalar_t__ self_ref; } ;
typedef  TYPE_2__ ws_data ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  METATABLE_WSCLIENT ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaM_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  realloc_headers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int websocketclient_gc(lua_State *L) {
  NODE_DBG("websocketclient_gc\n");

  ws_info *ws = (ws_info *) luaL_checkudata(L, 1, METATABLE_WSCLIENT);

  ws->extraHeaders = realloc_headers(ws->extraHeaders, 0);

  ws_data *data = (ws_data *) ws->reservedData;

  luaL_unref(L, LUA_REGISTRYINDEX, data->onConnection);
  luaL_unref(L, LUA_REGISTRYINDEX, data->onReceive);

  if (data->onClose != LUA_NOREF) {
    if (ws->connectionState != 4) { // only call if connection open
      lua_rawgeti(L, LUA_REGISTRYINDEX, data->onClose);

      lua_pushnumber(L, -100);
      lua_call(L, 1, 0);
    }
    luaL_unref(L, LUA_REGISTRYINDEX, data->onClose);
  }

  if (data->self_ref != LUA_NOREF) {
    lua_gc(L, LUA_GCSTOP, 0); // required to avoid freeing ws_data
    luaL_unref(L, LUA_REGISTRYINDEX, data->self_ref);
    data->self_ref = LUA_NOREF;
    lua_gc(L, LUA_GCRESTART, 0);
  }

  NODE_DBG("freeing lua data\n");
  luaM_free(L, data);
  NODE_DBG("done freeing lua data\n");

  return 0;
}