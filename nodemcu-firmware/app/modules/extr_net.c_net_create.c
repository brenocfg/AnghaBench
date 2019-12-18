#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {void* cb_accept_ref; } ;
struct TYPE_5__ {void* cb_sent_ref; void* cb_receive_ref; void* cb_dns_ref; int /*<<< orphan*/  wait_dns; int /*<<< orphan*/  hold; void* cb_disconnect_ref; void* cb_reconnect_ref; void* cb_connect_ref; } ;
struct TYPE_7__ {int type; TYPE_2__ server; TYPE_1__ client; int /*<<< orphan*/ * pcb; void* self_ref; } ;
typedef  TYPE_3__ lnet_userdata ;
typedef  enum net_type { ____Placeholder_net_type } net_type ;

/* Variables and functions */
 void* LUA_NOREF ; 
 char** NET_TABLES ; 
#define  TYPE_TCP_CLIENT 130 
#define  TYPE_TCP_SERVER 129 
#define  TYPE_UDP_SOCKET 128 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

lnet_userdata *net_create( lua_State *L, enum net_type type ) {
  const char *mt = NET_TABLES[type];
  lnet_userdata *ud = (lnet_userdata *)lua_newuserdata(L, sizeof(lnet_userdata));
  if (!ud) return NULL;
  luaL_getmetatable(L, mt);
  lua_setmetatable(L, -2);

  ud->type = type;
  ud->self_ref = LUA_NOREF;
  ud->pcb = NULL;

  switch (type) {
    case TYPE_TCP_CLIENT:
      ud->client.cb_connect_ref = LUA_NOREF;
      ud->client.cb_reconnect_ref = LUA_NOREF;
      ud->client.cb_disconnect_ref = LUA_NOREF;
      ud->client.hold = 0;
    case TYPE_UDP_SOCKET:
      ud->client.wait_dns = 0;
      ud->client.cb_dns_ref = LUA_NOREF;
      ud->client.cb_receive_ref = LUA_NOREF;
      ud->client.cb_sent_ref = LUA_NOREF;
      break;
    case TYPE_TCP_SERVER:
      ud->server.cb_accept_ref = LUA_NOREF;
      break;
  }
  return ud;
}