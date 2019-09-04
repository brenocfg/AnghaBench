#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct pbuf {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ cb_sent_ref; } ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ self_ref; int /*<<< orphan*/  tcp_pcb; TYPE_1__ client; int /*<<< orphan*/ * udp_pcb; int /*<<< orphan*/  pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ip_addr_t ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  PBUF_RAM ; 
 int /*<<< orphan*/  PBUF_TRANSPORT ; 
 int /*<<< orphan*/  TCP_WRITE_FLAG_COPY ; 
 scalar_t__ TYPE_TCP_CLIENT ; 
 scalar_t__ TYPE_TCP_SERVER ; 
 scalar_t__ TYPE_UDP_SOCKET ; 
 int /*<<< orphan*/  ipaddr_aton (char const*,TYPE_3__*) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_islightfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int lwip_lua_checkerr (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_udp_recv_cb ; 
 struct pbuf* pbuf_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 
 int /*<<< orphan*/  pbuf_take (struct pbuf*,char const*,size_t) ; 
 scalar_t__ tcp_write (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ udp_bind (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * udp_new () ; 
 int /*<<< orphan*/  udp_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ *) ; 
 scalar_t__ udp_sendto (int /*<<< orphan*/ *,struct pbuf*,TYPE_3__*,scalar_t__) ; 

int net_send( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud || ud->type == TYPE_TCP_SERVER)
    return luaL_error(L, "invalid user data");
  ip_addr_t addr;
  uint16_t port;
  const char *data;
  size_t datalen = 0;
  int stack = 2;
  if (ud->type == TYPE_UDP_SOCKET) {
    size_t dl = 0;
    port = luaL_checkinteger(L, stack++);
    if (port == 0) return luaL_error(L, "need port");
    const char *domain = luaL_checklstring(L, stack++, &dl);
    if (!domain) return luaL_error(L, "need IP address");
    if (!ipaddr_aton(domain, &addr)) return luaL_error(L, "invalid IP address");
  }
  data = luaL_checklstring(L, stack++, &datalen);
  if (!data || datalen == 0) return luaL_error(L, "no data to send");
  if (lua_isfunction(L, stack) || lua_islightfunction(L, stack)) {
    lua_pushvalue(L, stack++);
    luaL_unref(L, LUA_REGISTRYINDEX, ud->client.cb_sent_ref);
    ud->client.cb_sent_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  if (ud->type == TYPE_UDP_SOCKET && !ud->pcb) {
    ud->udp_pcb = udp_new();
    if (!ud->udp_pcb)
      return luaL_error(L, "cannot allocate PCB");
    udp_recv(ud->udp_pcb, net_udp_recv_cb, ud);
    ip_addr_t laddr = {0};
    err_t err = udp_bind(ud->udp_pcb, &laddr, 0);
    if (err != ERR_OK) {
      udp_remove(ud->udp_pcb);
      ud->udp_pcb = NULL;
      return lwip_lua_checkerr(L, err);
    }
    if (ud->self_ref == LUA_NOREF) {
      lua_pushvalue(L, 1);
      ud->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
  }
  if (!ud->pcb || ud->self_ref == LUA_NOREF)
    return luaL_error(L, "not connected");
  err_t err;
  if (ud->type == TYPE_UDP_SOCKET) {
    struct pbuf *pb = pbuf_alloc(PBUF_TRANSPORT, datalen, PBUF_RAM);
    if (!pb)
      return luaL_error(L, "cannot allocate message buffer");
    pbuf_take(pb, data, datalen);
    err = udp_sendto(ud->udp_pcb, pb, &addr, port);
    pbuf_free(pb);
    if (ud->client.cb_sent_ref != LUA_NOREF) {
      lua_rawgeti(L, LUA_REGISTRYINDEX, ud->client.cb_sent_ref);
      lua_rawgeti(L, LUA_REGISTRYINDEX, ud->self_ref);
      lua_call(L, 1, 0);
    }
  } else if (ud->type == TYPE_TCP_CLIENT) {
    err = tcp_write(ud->tcp_pcb, data, datalen, TCP_WRITE_FLAG_COPY);
  }
  return lwip_lua_checkerr(L, err);
}