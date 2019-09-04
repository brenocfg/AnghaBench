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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU160MHZ ; 
 scalar_t__ CPU80MHZ ; 
 int /*<<< orphan*/  REG_CLR_BIT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ets_get_cpu_frequency () ; 
 int /*<<< orphan*/  ets_update_cpu_frequency (scalar_t__) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int node_setcpufreq(lua_State* L)
{
  // http://www.esp8266.com/viewtopic.php?f=21&t=1369
  uint32_t new_freq = luaL_checkinteger(L, 1);
  if (new_freq == CPU160MHZ){
    REG_SET_BIT(0x3ff00014, BIT(0));
    ets_update_cpu_frequency(CPU160MHZ);
  } else {
    REG_CLR_BIT(0x3ff00014,  BIT(0));
    ets_update_cpu_frequency(CPU80MHZ);
  }
  new_freq = ets_get_cpu_frequency();
  lua_pushinteger(L, new_freq);
  return 1;
}