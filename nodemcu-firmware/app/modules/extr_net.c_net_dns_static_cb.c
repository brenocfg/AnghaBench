#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int addr; } ;
typedef  TYPE_1__ ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IP2STR (int*) ; 
 char* IPSTR ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void net_dns_static_cb(const char *name, ip_addr_t *ipaddr, void *callback_arg) {
  ip_addr_t addr;
  if (ipaddr != NULL)
    addr = *ipaddr;
  else addr.addr = 0xFFFFFFFF;
  int cb_ref = ((int*)callback_arg)[0];
  free(callback_arg);
  lua_State *L = lua_getstate();

  lua_rawgeti(L, LUA_REGISTRYINDEX, cb_ref);
  lua_pushnil(L);
  if (addr.addr != 0xFFFFFFFF) {
    char iptmp[20];
    size_t ipl = sprintf(iptmp, IPSTR, IP2STR(&addr.addr));
    lua_pushlstring(L, iptmp, ipl);
  } else {
    lua_pushnil(L);
  }
  lua_call(L, 2, 0);

  luaL_unref(L, LUA_REGISTRYINDEX, cb_ref);
}