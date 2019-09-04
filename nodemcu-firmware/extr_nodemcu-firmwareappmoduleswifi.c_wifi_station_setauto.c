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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wifi_station_set_auto_connect (unsigned int) ; 

__attribute__((used)) static int wifi_station_setauto( lua_State* L )
{
  unsigned a;

  a = luaL_checkinteger( L, 1 );
  luaL_argcheck(L, ( a == 0 || a == 1 ), 1, "0 or 1");
  wifi_station_set_auto_connect(a);
  return 0;
}