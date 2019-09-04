#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NET_TABLE_TCP_CLIENT ; 
 int /*<<< orphan*/  NET_TABLE_TCP_SERVER ; 
 int /*<<< orphan*/  NET_TABLE_UDP_SOCKET ; 
 int /*<<< orphan*/  igmp_init () ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ net_tcpserver_map ; 
 scalar_t__ net_tcpsocket_map ; 
 scalar_t__ net_udpsocket_map ; 

int luaopen_net( lua_State *L ) {
  igmp_init();

  luaL_rometatable(L, NET_TABLE_TCP_SERVER, (void *)net_tcpserver_map);
  luaL_rometatable(L, NET_TABLE_TCP_CLIENT, (void *)net_tcpsocket_map);
  luaL_rometatable(L, NET_TABLE_UDP_SOCKET, (void *)net_udpsocket_map);

  return 0;
}