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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  ipaddr_addr (char const*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t parse_key(lua_State* L, const char * key){
  lua_getfield(L, 1, key);
  if( lua_isstring(L, -1) )   // deal with the ip/netmask/gw string
  {
    const char *ip = luaL_checkstring( L, -1 );
    return ipaddr_addr(ip);
  }
  lua_pop(L, 1);
  return 0;
}