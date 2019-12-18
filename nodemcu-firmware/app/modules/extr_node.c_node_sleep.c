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
 int /*<<< orphan*/  dbg_printf (char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int node_sleep( lua_State* L )
{
  dbg_printf("\n The options \"TIMER_SUSPEND_ENABLE\" and \"PMSLEEP_ENABLE\" in \"app/include/user_config.h\" were disabled during FW build!\n");
  return luaL_error(L, "node.sleep() is unavailable");
}