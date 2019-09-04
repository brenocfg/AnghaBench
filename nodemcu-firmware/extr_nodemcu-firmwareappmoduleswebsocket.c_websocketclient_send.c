#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int connectionState; scalar_t__ reservedData; } ;
typedef  TYPE_1__ ws_info ;
typedef  int /*<<< orphan*/  ws_data ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  METATABLE_WSCLIENT ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ws_send (TYPE_1__*,int,char const*,unsigned short) ; 

__attribute__((used)) static int websocketclient_send(lua_State *L) {
  NODE_DBG("websocketclient_send is called.\n");

  ws_info *ws = (ws_info *) luaL_checkudata(L, 1, METATABLE_WSCLIENT);

  ws_data *data = (ws_data *) ws->reservedData;

  if (ws->connectionState != 3) {
    // should this be an onFailure callback instead?
    return luaL_error(L, "Websocket isn't connected.\n");
  }

  int msgLength;
  const char *msg = luaL_checklstring(L, 2, &msgLength);

  int opCode = 1; // default: text message
  if (lua_gettop(L) == 3) {
    opCode = luaL_checkint(L, 3);
  }

  ws_send(ws, opCode, msg, (unsigned short) msgLength);
  return 0;
}