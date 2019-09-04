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
struct tcp_pcb {int keep_idle; int keep_cnt; int /*<<< orphan*/  so_options; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ cb_accept_ref; int timeout; } ;
struct TYPE_7__ {scalar_t__ type; scalar_t__ self_ref; struct tcp_pcb* tcp_pcb; TYPE_1__ server; int /*<<< orphan*/  pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ABRT ; 
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  SOF_KEEPALIVE ; 
 int /*<<< orphan*/  TYPE_TCP_CLIENT ; 
 scalar_t__ TYPE_TCP_SERVER ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  net_connected_cb (TYPE_2__*,struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 TYPE_2__* net_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_err_cb ; 
 int /*<<< orphan*/  net_sent_cb ; 
 int /*<<< orphan*/  net_tcp_recv_cb ; 
 int /*<<< orphan*/  tcp_accepted (struct tcp_pcb*) ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,TYPE_2__*) ; 
 int /*<<< orphan*/  tcp_err (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static err_t net_accept_cb(void *arg, struct tcp_pcb *newpcb, err_t err) {
  lnet_userdata *ud = (lnet_userdata*)arg;
  if (!ud || ud->type != TYPE_TCP_SERVER || !ud->pcb) return ERR_ABRT;
  if (ud->self_ref == LUA_NOREF || ud->server.cb_accept_ref == LUA_NOREF) return ERR_ABRT;

  lua_State *L = lua_getstate();
  lua_rawgeti(L, LUA_REGISTRYINDEX, ud->server.cb_accept_ref);

  lnet_userdata *nud = net_create(L, TYPE_TCP_CLIENT);
  lua_pushvalue(L, 2);
  nud->self_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  nud->tcp_pcb = newpcb;
  tcp_arg(nud->tcp_pcb, nud);
  tcp_err(nud->tcp_pcb, net_err_cb);
  tcp_recv(nud->tcp_pcb, net_tcp_recv_cb);
  tcp_sent(nud->tcp_pcb, net_sent_cb);
  nud->tcp_pcb->so_options |= SOF_KEEPALIVE;
  nud->tcp_pcb->keep_idle = ud->server.timeout * 1000;
  nud->tcp_pcb->keep_cnt = 1;
  tcp_accepted(ud->tcp_pcb);

  lua_call(L, 1, 0);

  return net_connected_cb(nud, nud->tcp_pcb, ERR_OK);
}