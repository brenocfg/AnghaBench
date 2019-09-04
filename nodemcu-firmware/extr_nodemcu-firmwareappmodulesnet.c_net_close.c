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
struct TYPE_4__ {scalar_t__ wait_dns; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  self_ref; TYPE_1__ client; int /*<<< orphan*/ * pcb; int /*<<< orphan*/ * udp_pcb; int /*<<< orphan*/ * tcp_pcb; } ;
typedef  TYPE_2__ lnet_userdata ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  LUA_GCRESTART ; 
 int /*<<< orphan*/  LUA_GCSTOP ; 
 int /*<<< orphan*/  LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  TYPE_TCP_CLIENT 130 
#define  TYPE_TCP_SERVER 129 
#define  TYPE_UDP_SOCKET 128 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_remove (int /*<<< orphan*/ *) ; 

int net_close( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud) return luaL_error(L, "invalid user data");
  if (ud->pcb) {
    switch (ud->type) {
      case TYPE_TCP_CLIENT:
        if (ERR_OK != tcp_close(ud->tcp_pcb)) {
          tcp_arg(ud->tcp_pcb, NULL);
          tcp_abort(ud->tcp_pcb);
        }
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
  } else {
    return luaL_error(L, "not connected");
  }
  if (ud->type == TYPE_TCP_SERVER ||
     (ud->pcb == NULL && ud->client.wait_dns == 0)) {
    lua_gc(L, LUA_GCSTOP, 0);
    luaL_unref(L, LUA_REGISTRYINDEX, ud->self_ref);
    ud->self_ref = LUA_NOREF;
    lua_gc(L, LUA_GCRESTART, 0);
  }
  return 0;
}