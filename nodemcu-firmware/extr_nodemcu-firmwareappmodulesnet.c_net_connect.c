#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {scalar_t__ cb_connect_ref; int /*<<< orphan*/  wait_dns; } ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ self_ref; TYPE_3__* tcp_pcb; TYPE_1__ client; scalar_t__ pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
typedef  int /*<<< orphan*/  ip_addr_t ;
typedef  scalar_t__ err_t ;
struct TYPE_16__ {scalar_t__ remote_port; } ;

/* Variables and functions */
 scalar_t__ ERR_INPROGRESS ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ TYPE_TCP_CLIENT ; 
 scalar_t__ dns_gethostbyname (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char const*,int /*<<< orphan*/ *,TYPE_2__*),TYPE_2__*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_islightfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int lwip_lua_checkerr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  net_dns_cb (char const*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  net_err_cb ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_sent_cb ; 
 int /*<<< orphan*/  net_tcp_recv_cb ; 
 int /*<<< orphan*/  tcp_abort (TYPE_3__*) ; 
 int /*<<< orphan*/  tcp_arg (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tcp_err (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* tcp_new () ; 
 int /*<<< orphan*/  tcp_recv (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (TYPE_3__*,int /*<<< orphan*/ ) ; 

int net_connect( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud || ud->type != TYPE_TCP_CLIENT)
    return luaL_error(L, "invalid user data");
  if (ud->pcb)
    return luaL_error(L, "already connected");
  uint16_t port = luaL_checkinteger(L, 2);
  if (port == 0)
    return luaL_error(L, "specify port");
  const char *domain = "127.0.0.1";
  if (lua_isstring(L, 3)) {
    size_t dl = 0;
    domain = luaL_checklstring(L, 3, &dl);
  }
  if (lua_gettop(L) > 3) {
    luaL_argcheck(L, lua_isfunction(L, 4) || lua_islightfunction(L, 4), 4, "not a function");
    lua_pushvalue(L, 4);
    luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_connect_ref);
    ud->client.cb_connect_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  ud->tcp_pcb = tcp_new();
  if (!ud->tcp_pcb)
    return luaL_error(L, "cannot allocate PCB");
  tcp_arg(ud->tcp_pcb, ud);
  tcp_err(ud->tcp_pcb, net_err_cb);
  tcp_recv(ud->tcp_pcb, net_tcp_recv_cb);
  tcp_sent(ud->tcp_pcb, net_sent_cb);
  ud->tcp_pcb->remote_port = port;
  ip_addr_t addr;
  ud->client.wait_dns ++;
  int unref = 0;
  if (ud->self_ref == LUA_NOREF) {
    unref = 1;
    lua_pushvalue(L, 1);
    ud->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  err_t err = dns_gethostbyname(domain, &addr, net_dns_cb, ud);
  if (err == ERR_OK) {
    net_dns_cb(domain, &addr, ud);
  } else if (err != ERR_INPROGRESS) {
    ud->client.wait_dns --;
    if (unref) {
      luaL_unref(L, LUA_REGISTRYINDEX, ud->self_ref);
      ud->self_ref = LUA_NOREF;
    }
    tcp_abort(ud->tcp_pcb);
    ud->tcp_pcb = NULL;
    return lwip_lua_checkerr(L, err);
  }
  return 0;
}