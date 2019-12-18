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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mac ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_MAC_STR ; 
 int /*<<< orphan*/  ets_str2macaddr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,unsigned int*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  wifi_softap_deauth (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wifi_ap_deauth( lua_State* L )
{
  uint8_t mac[6];
  unsigned len = 0;
  if(lua_isstring(L, 1))
  {
    const char *macaddr = luaL_checklstring( L, 1, &len );
    luaL_argcheck(L, len==17, 1, INVALID_MAC_STR);
    ets_str2macaddr(mac, macaddr);
  }
  else
  {
    memset(&mac, 0xFF, sizeof(mac));
  }
  lua_pushboolean(L,wifi_softap_deauth(mac));
  return 1;
}