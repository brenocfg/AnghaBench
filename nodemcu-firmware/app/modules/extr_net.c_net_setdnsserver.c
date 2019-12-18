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
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int DNS_MAX_SERVERS ; 
 scalar_t__ IPADDR_ANY ; 
 scalar_t__ IPADDR_NONE ; 
 int /*<<< orphan*/  dns_setserver (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip4_addr_set_u32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ipaddr_addr (char const*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int luaL_optint (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_setdnsserver( lua_State* L ) {
  size_t l;
  u32_t ip32;

  const char *server = luaL_checklstring( L, 1, &l );
  if (l>16 || server == NULL || (ip32 = ipaddr_addr(server)) == IPADDR_NONE || ip32 == IPADDR_ANY)
    return luaL_error( L, "invalid dns server ip" );

  int numdns = luaL_optint(L, 2, 0);
  if (numdns >= DNS_MAX_SERVERS)
    return luaL_error( L, "server index out of range [0-%d]", DNS_MAX_SERVERS - 1);

  ip_addr_t ipaddr;
  ip4_addr_set_u32(&ipaddr, ip32);
  dns_setserver(numdns,&ipaddr);

  return 0;
}