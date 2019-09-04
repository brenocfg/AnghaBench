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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 unsigned int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  system_phy_set_max_tpw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wifi_setmaxtxpower( lua_State* L )
{
  unsigned power;
  power = luaL_checkinteger( L, 1 );
  luaL_argcheck(L, (power > 0 && power < 83), 1, "tx power out of range (0->82)");

  system_phy_set_max_tpw( (uint8_t) power);
  return 1;
}