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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_station_ap_change (int) ; 

__attribute__((used)) static int wifi_station_change_ap( lua_State* L )
{
  uint8 ap_index=luaL_checkinteger(L, 1);
  luaL_argcheck(L, (ap_index >= 1 && ap_index <= 5), 1, "Valid range: 1-5");
  lua_pushboolean(L, wifi_station_ap_change(ap_index-1));
  return 1;
}