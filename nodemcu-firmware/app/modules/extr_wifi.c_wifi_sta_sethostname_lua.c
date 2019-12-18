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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_sta_checkhostname (char const*,size_t) ; 
 int /*<<< orphan*/  wifi_station_set_hostname (char*) ; 

__attribute__((used)) static int wifi_sta_sethostname_lua( lua_State* L )
{
  size_t len;
  const char *hostname = luaL_checklstring(L, 1, &len);
  luaL_argcheck(L, wifi_sta_checkhostname(hostname, len), 1, "Invalid hostname");
  lua_pushboolean(L, wifi_station_set_hostname((char*)hostname));
  return 1;
}