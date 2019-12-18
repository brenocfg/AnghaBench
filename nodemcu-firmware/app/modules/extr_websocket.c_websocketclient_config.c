#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* extraHeaders; scalar_t__ reservedData; } ;
typedef  TYPE_1__ ws_info ;
typedef  int /*<<< orphan*/  ws_data ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/ * value; void* key; } ;
typedef  TYPE_2__ header_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  METATABLE_WSCLIENT ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* realloc_headers (TYPE_2__*,int) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int websocketclient_config(lua_State *L) {
  NODE_DBG("websocketclient_config is called.\n");

  ws_info *ws = (ws_info *) luaL_checkudata(L, 1, METATABLE_WSCLIENT);

  ws_data *data = (ws_data *) ws->reservedData;

  luaL_checktype(L, 2, LUA_TTABLE);
  lua_getfield(L, 2, "headers");
  if(lua_istable(L, -1)) {

    lua_pushnil(L);
    int size = 0;
    while(lua_next(L, -2)) {
      size++;
      lua_pop(L, 1);
    }

    ws->extraHeaders = realloc_headers(ws->extraHeaders, size);
    if(ws->extraHeaders) {
      header_t *header = ws->extraHeaders;

      lua_pushnil(L);
      while(lua_next(L, -2)) {
        header->key = strdup(lua_tostring(L, -2));
        header->value = strdup(lua_tostring(L, -1));
        header++;
        lua_pop(L, 1);
      }

      header->key = header->value = NULL;
    }
  }
  lua_pop(L, 1); // pop headers

  return 0;
}