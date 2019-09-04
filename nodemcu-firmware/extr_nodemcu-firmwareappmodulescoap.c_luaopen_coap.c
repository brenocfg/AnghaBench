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
 scalar_t__ coap_client_map ; 
 scalar_t__ coap_server_map ; 
 int /*<<< orphan*/  endpoint_setup () ; 
 int /*<<< orphan*/  luaL_rometatable (int /*<<< orphan*/ *,char*,void*) ; 

int luaopen_coap( lua_State *L )
{
  endpoint_setup();
  luaL_rometatable(L, "coap_server", (void *)coap_server_map);  // create metatable for coap_server
  luaL_rometatable(L, "coap_client", (void *)coap_client_map);  // create metatable for coap_client
  return 0;
}