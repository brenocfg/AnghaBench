#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16_t ;
struct pbuf {struct pbuf* next; int /*<<< orphan*/  len; int /*<<< orphan*/  payload; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ cb_receive_ref; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ self_ref; TYPE_1__ client; } ;
typedef  TYPE_2__ lnet_userdata ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_3__ ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPSTR ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ TYPE_UDP_SOCKET ; 
 int /*<<< orphan*/  ets_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pbuf_free (struct pbuf*) ; 

__attribute__((used)) static void net_recv_cb(lnet_userdata *ud, struct pbuf *p, ip_addr_t *addr, u16_t port) {
  if (ud->client.cb_receive_ref == LUA_NOREF) {
    pbuf_free(p);
    return;
  }

  int num_args = 2;
  char iptmp[16] = { 0, };
  if (ud->type == TYPE_UDP_SOCKET)
  {
    num_args += 2;
    ets_sprintf(iptmp, IPSTR, IP2STR(&addr->addr));
  }

  lua_State *L = lua_getstate();
  struct pbuf *pp = p;
  while (pp)
  {
    lua_rawgeti(L, LUA_REGISTRYINDEX, ud->client.cb_receive_ref);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ud->self_ref);
    lua_pushlstring(L, pp->payload, pp->len);
    if (ud->type == TYPE_UDP_SOCKET) {
      lua_pushinteger(L, port);
      lua_pushstring(L, iptmp);
    }
    lua_call(L, num_args, 0);
    pp = pp->next;
  }
  pbuf_free(p);
}