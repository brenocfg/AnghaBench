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
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ wifi_station_get_current_ap_id () ; 

__attribute__((used)) static int wifi_station_get_ap_index( lua_State* L )
{
  lua_pushnumber(L, wifi_station_get_current_ap_id()+1);
  return 1;
}