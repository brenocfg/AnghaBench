#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  callbackDone; scalar_t__ success; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int STATION_MODE ; 
 int /*<<< orphan*/  enduser_setup_ap_stop () ; 
 int /*<<< orphan*/  enduser_setup_connected_callback () ; 
 int /*<<< orphan*/  enduser_setup_dns_stop () ; 
 int /*<<< orphan*/  enduser_setup_free () ; 
 int /*<<< orphan*/  enduser_setup_http_stop () ; 
 int /*<<< orphan*/  manual ; 
 TYPE_1__* state ; 
 int wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_opmode (int) ; 
 int /*<<< orphan*/  wifi_station_connect () ; 

__attribute__((used)) static int enduser_setup_stop(lua_State* L)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_stop");

  if (!manual)
  {
    enduser_setup_ap_stop();
  }
  if (state != NULL && state->success && !state->callbackDone)
  {
    wifi_set_opmode(STATION_MODE | wifi_get_opmode());
    wifi_station_connect();
    enduser_setup_connected_callback();
  }
  enduser_setup_dns_stop();
  enduser_setup_http_stop();
  enduser_setup_free();

  return 0;
}