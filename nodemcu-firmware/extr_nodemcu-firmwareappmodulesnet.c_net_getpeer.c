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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* tcp_pcb; int /*<<< orphan*/  pcb; } ;
typedef  TYPE_2__ lnet_userdata ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_3__ ip_addr_t ;
struct TYPE_5__ {scalar_t__ remote_port; TYPE_3__ remote_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPSTR ; 
 scalar_t__ TYPE_TCP_CLIENT ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  ets_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* net_get_udata (int /*<<< orphan*/ *) ; 

int net_getpeer( lua_State *L ) {
  lnet_userdata *ud = net_get_udata(L);
  if (!ud || ud->type != TYPE_TCP_CLIENT)
    return luaL_error(L, "invalid user data");
  if (!ud->pcb) {
    lua_pushnil(L);
    lua_pushnil(L);
    return 2;
  }
  uint16_t port = ud->tcp_pcb->remote_port;
  ip_addr_t addr = ud->tcp_pcb->remote_ip;
  if (port == 0) {
    lua_pushnil(L);
    lua_pushnil(L);
    return 2;
  }
  char addr_str[16];
  bzero(addr_str, 16);
  ets_sprintf(addr_str, IPSTR, IP2STR(&addr.addr));
  lua_pushinteger(L, port);
  lua_pushstring(L, addr_str);
  return 2;
}