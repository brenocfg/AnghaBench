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
struct TYPE_5__ {void* cb_sent_ref; void* cb_receive_ref; void* cb_dns_ref; void* cb_reconnect_ref; void* cb_disconnect_ref; void* cb_connect_ref; } ;
struct TYPE_7__ {int type; void* self_ref; TYPE_2__ server; TYPE_1__ client; int /*<<< orphan*/ * udp_pcb; int /*<<< orphan*/ * tcp_pcb; scalar_t__ pcb; } ;
typedef  TYPE_3__ lnet_userdata ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  TYPE_TCP_CLIENT 130 
#define  TYPE_TCP_SERVER 129 
#define  TYPE_UDP_SOCKET 128 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ *) ; 

int net_delete( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud) return luaL_error(L, "no user data");
  if (ud->pcb) {
    switch (ud->type) {
      case TYPE_TCP_CLIENT:
        tcp_arg(ud->tcp_pcb, NULL);
        tcp_abort(ud->tcp_pcb);
        ud->tcp_pcb = NULL;
        break;
      case TYPE_TCP_SERVER:
        tcp_close(ud->tcp_pcb);
        ud->tcp_pcb = NULL;
        break;
      case TYPE_UDP_SOCKET:
        udp_remove(ud->udp_pcb);
        ud->udp_pcb = NULL;
        break;
    }
  }
  switch (ud->type) {
    case TYPE_TCP_CLIENT:
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_connect_ref);
      ud->client.cb_connect_ref = LUA_NOREF;
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_disconnect_ref);
      ud->client.cb_disconnect_ref = LUA_NOREF;
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_reconnect_ref);
      ud->client.cb_reconnect_ref = LUA_NOREF;
    case TYPE_UDP_SOCKET:
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_dns_ref);
      ud->client.cb_dns_ref = LUA_NOREF;
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_receive_ref);
      ud->client.cb_receive_ref = LUA_NOREF;
      luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_sent_ref);
      ud->client.cb_sent_ref = LUA_NOREF;
      break;
    case TYPE_TCP_SERVER:
      luaL_unref(L, LUA_REGISTRYINDEX, ud->server.cb_accept_ref);
      ud->server.cb_accept_ref = LUA_NOREF;
      break;
  }
  lua_gc(L, LUA_GCSTOP, 0);
  luaL_unref(L, LUA_REGISTRYINDEX, ud->self_ref);
  ud->self_ref = LUA_NOREF;
  lua_gc(L, LUA_GCRESTART, 0);
  return 0;
}