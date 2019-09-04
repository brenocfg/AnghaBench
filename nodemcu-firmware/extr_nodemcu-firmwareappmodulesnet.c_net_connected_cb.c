#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcp_pcb {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {scalar_t__ cb_connect_ref; } ;
struct TYPE_4__ {scalar_t__ self_ref; TYPE_1__ client; struct tcp_pcb* pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_ABRT ; 
 scalar_t__ ERR_OK ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  net_err_cb (void*,scalar_t__) ; 

__attribute__((used)) static err_t net_connected_cb(void *arg, struct tcp_pcb *tpcb, err_t err) {
  lnet_userdata *ud = (lnet_userdata*)arg;
  if (!ud || ud->pcb != tpcb) return ERR_ABRT;
  if (err != ERR_OK) {
    net_err_cb(arg, err);
    return ERR_ABRT;
  }
  lua_State *L = lua_getstate();
  if (ud->self_ref != LUA_NOREF && ud->client.cb_connect_ref != LUA_NOREF) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, ud->client.cb_connect_ref);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ud->self_ref);
    lua_call(L, 1, 0);
  }
  return ERR_OK;
}