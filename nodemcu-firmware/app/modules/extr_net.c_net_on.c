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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int cb_connect_ref; int cb_disconnect_ref; int cb_reconnect_ref; int cb_dns_ref; int cb_receive_ref; int cb_sent_ref; } ;
struct TYPE_5__ {int type; TYPE_1__ client; } ;
typedef  TYPE_2__ lnet_userdata ;

/* Variables and functions */
 int LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  TYPE_TCP_CLIENT 129 
 int TYPE_TCP_SERVER ; 
#define  TYPE_UDP_SOCKET 128 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_islightfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

int net_on( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud || ud->type == TYPE_TCP_SERVER)
    return luaL_error(L, "invalid user data");
  int *refptr = NULL;
  const char *name = luaL_checkstring(L, 2);
  if (!name) return luaL_error(L, "need callback name");
  switch (ud->type) {
    case TYPE_TCP_CLIENT:
      if (strcmp("connection",name)==0)
        { refptr = &ud->client.cb_connect_ref; break; }
      if (strcmp("disconnection",name)==0)
        { refptr = &ud->client.cb_disconnect_ref; break; }
      if (strcmp("reconnection",name)==0)
        { refptr = &ud->client.cb_reconnect_ref; break; }
    case TYPE_UDP_SOCKET:
      if (strcmp("dns",name)==0)
        { refptr = &ud->client.cb_dns_ref; break; }
      if (strcmp("receive",name)==0)
        { refptr = &ud->client.cb_receive_ref; break; }
      if (strcmp("sent",name)==0)
        { refptr = &ud->client.cb_sent_ref; break; }
      break;
    default: return luaL_error(L, "invalid user data");
  }
  if (refptr == NULL)
    return luaL_error(L, "invalid callback name");
  if (lua_isfunction(L, 3) || lua_islightfunction(L, 3)) {
    lua_pushvalue(L, 3);
    luaL_unref(L, LUA_REGISTRYINDEX, *refptr);
    *refptr = luaL_ref(L, LUA_REGISTRYINDEX);
  } else if (lua_isnil(L, 3)) {
    luaL_unref(L, LUA_REGISTRYINDEX, *refptr);
    *refptr = LUA_NOREF;
  } else {
    return luaL_error(L, "invalid callback function");
  }
  return 0;
}