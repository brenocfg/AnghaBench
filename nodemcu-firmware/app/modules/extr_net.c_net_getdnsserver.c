#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ ip_addr_t ;

/* Variables and functions */
 int DNS_MAX_SERVERS ; 
 int /*<<< orphan*/  IP2STR (int /*<<< orphan*/ *) ; 
 char* IPSTR ; 
 TYPE_1__ dns_getserver (int) ; 
 scalar_t__ ip_addr_isany (TYPE_1__*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_getdnsserver( lua_State* L ) {
  int numdns = luaL_optint(L, 1, 0);
  if (numdns >= DNS_MAX_SERVERS)
    return luaL_error( L, "server index out of range [0-%d]", DNS_MAX_SERVERS - 1);

  // ip_addr_t ipaddr;
  // dns_getserver(numdns,&ipaddr);
  // Bug fix by @md5crypt https://github.com/nodemcu/nodemcu-firmware/pull/500
  ip_addr_t ipaddr = dns_getserver(numdns);

  if ( ip_addr_isany(&ipaddr) ) {
    lua_pushnil( L );
  } else {
    char temp[20] = {0};
    sprintf(temp, IPSTR, IP2STR( &ipaddr.addr ) );
    lua_pushstring( L, temp );
  }

  return 1;
}