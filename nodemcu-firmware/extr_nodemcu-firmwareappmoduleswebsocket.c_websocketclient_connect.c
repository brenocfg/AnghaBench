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
struct TYPE_4__ {int connectionState; scalar_t__ reservedData; } ;
typedef  TYPE_1__ ws_info ;
struct TYPE_5__ {int /*<<< orphan*/  self_ref; } ;
typedef  TYPE_2__ ws_data ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  METATABLE_WSCLIENT ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ws_connect (TYPE_1__*,char const*) ; 

__attribute__((used)) static int websocketclient_connect(lua_State *L) {
  NODE_DBG("websocketclient_connect is called.\n");

  ws_info *ws = (ws_info *) luaL_checkudata(L, 1, METATABLE_WSCLIENT);

  ws_data *data = (ws_data *) ws->reservedData;

  if (ws->connectionState != 0 && ws->connectionState != 4) {
    return luaL_error(L, "Websocket already connecting or connected.\n");
  }
  ws->connectionState = 0;

  lua_pushvalue(L, 1);  // copy userdata to the top of stack to allow ref
  data->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);

  const char *url = luaL_checkstring(L, 2);
  ws_connect(ws, url);

  return 0;
}