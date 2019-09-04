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
typedef  int /*<<< orphan*/  ws_info ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  METATABLE_WSCLIENT ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int websocketclient_close(lua_State *L) {
  NODE_DBG("websocketclient_close.\n");
  ws_info *ws = (ws_info *) luaL_checkudata(L, 1, METATABLE_WSCLIENT);

  ws_close(ws);
  return 0;
}