#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct tcp_pcb {int /*<<< orphan*/  so_options; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {void* cb_accept_ref; } ;
struct TYPE_7__ {int type; scalar_t__ self_ref; int /*<<< orphan*/ * udp_pcb; struct tcp_pcb* tcp_pcb; TYPE_1__ server; scalar_t__ pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_MEM ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  SOF_REUSEADDR ; 
 int TYPE_TCP_CLIENT ; 
#define  TYPE_TCP_SERVER 129 
#define  TYPE_UDP_SOCKET 128 
 int /*<<< orphan*/  ipaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_islightfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lwip_lua_checkerr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_accept_cb ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_udp_recv_cb ; 
 int /*<<< orphan*/  tcp_accept (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,TYPE_2__*) ; 
 scalar_t__ tcp_bind (struct tcp_pcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_close (struct tcp_pcb*) ; 
 struct tcp_pcb* tcp_listen (struct tcp_pcb*) ; 
 struct tcp_pcb* tcp_new () ; 
 scalar_t__ udp_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * udp_new () ; 
 int /*<<< orphan*/  udp_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ *) ; 

int net_listen( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud || ud->type == TYPE_TCP_CLIENT)
    return luaL_error(L, "invalid user data");
  if (ud->pcb)
    return luaL_error(L, "already listening");
  int stack = 2;
  uint16_t port = 0;
  const char *domain = "0.0.0.0";
  if (lua_isnumber(L, stack))
    port = lua_tointeger(L, stack++);
  if (lua_isstring(L, stack)) {
    size_t dl = 0;
    domain = luaL_checklstring(L, stack++, &dl);
  }
  ip_addr_t addr;
  if (!ipaddr_aton(domain, &addr))
    return luaL_error(L, "invalid IP address");
  if (ud->type == TYPE_TCP_SERVER) {
    if (lua_isfunction(L, stack) || lua_islightfunction(L, stack)) {
      lua_pushvalue(L, stack++);
      luaL_unref(L, LUA_REGISTRYINDEX, ud->server.cb_accept_ref);
      ud->server.cb_accept_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
      return luaL_error(L, "need callback");
    }
  }
  err_t err = ERR_OK;
  switch (ud->type) {
    case TYPE_TCP_SERVER:
      ud->tcp_pcb = tcp_new();
      if (!ud->tcp_pcb)
        return luaL_error(L, "cannot allocate PCB");
      ud->tcp_pcb->so_options |= SOF_REUSEADDR;
      err = tcp_bind(ud->tcp_pcb, &addr, port);
      if (err == ERR_OK) {
        tcp_arg(ud->tcp_pcb, ud);
        struct tcp_pcb *pcb = tcp_listen(ud->tcp_pcb);
        if (!pcb) {
          err = ERR_MEM;
        } else {
          ud->tcp_pcb = pcb;
          tcp_accept(ud->tcp_pcb, net_accept_cb);
        }
      }
      break;
    case TYPE_UDP_SOCKET:
      ud->udp_pcb = udp_new();
      if (!ud->udp_pcb)
        return luaL_error(L, "cannot allocate PCB");
      udp_recv(ud->udp_pcb, net_udp_recv_cb, ud);
      err = udp_bind(ud->udp_pcb, &addr, port);
      break;
  }
  if (err != ERR_OK) {
    switch (ud->type) {
      case TYPE_TCP_SERVER:
        tcp_close(ud->tcp_pcb);
        ud->tcp_pcb = NULL;
        break;
      case TYPE_UDP_SOCKET:
        udp_remove(ud->udp_pcb);
        ud->udp_pcb = NULL;
        break;
    }
    return lwip_lua_checkerr(L, err);
  }
  if (ud->self_ref == LUA_NOREF) {
    lua_pushvalue(L, 1);
    ud->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  return 0;
}