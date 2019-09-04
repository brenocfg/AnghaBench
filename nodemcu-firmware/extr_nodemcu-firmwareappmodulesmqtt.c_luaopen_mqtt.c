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
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 
 scalar_t__ mqtt_socket_map ; 

int luaopen_mqtt( lua_State *L )
{
  luaL_rometatable(L, "mqtt.socket", (void *)mqtt_socket_map);  // create metatable for mqtt.socket
  return 0;
}