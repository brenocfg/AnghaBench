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
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int STATION_MODE ; 
 int /*<<< orphan*/  do_station_cfg ; 
 scalar_t__ do_station_cfg_handle ; 
 int /*<<< orphan*/  enduser_setup_check_station_start () ; 
 scalar_t__ enduser_setup_dns_start () ; 
 scalar_t__ enduser_setup_http_start () ; 
 scalar_t__ enduser_setup_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enduser_setup_stop (int /*<<< orphan*/ ) ; 
 char* ipaddr ; 
 int /*<<< orphan*/  lua_getstate () ; 
 int /*<<< orphan*/  manual ; 
 int /*<<< orphan*/  on_initial_scan_done ; 
 scalar_t__ task_get_id (int /*<<< orphan*/ ) ; 
 int wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_opmode (int) ; 
 int /*<<< orphan*/  wifi_station_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enduser_setup_start(lua_State *L)
{
  /* Note: The debug callback is set in enduser_setup_init. It's normal to not see this debug message on first invocation. */
  ENDUSER_SETUP_DEBUG("enduser_setup_start");

  ipaddr[0] = '\0';

  if (!do_station_cfg_handle)
  {
    do_station_cfg_handle = task_get_id(do_station_cfg);
  }

  if(enduser_setup_init(L))
  {
    goto failed;
  }

  if (!manual)
  {
    ENDUSER_SETUP_DEBUG("Performing AP Scan to identify likely AP's channel. Enabling Station if it wasn't already.");
    wifi_set_opmode(STATION_MODE | wifi_get_opmode());
    wifi_station_scan(NULL, on_initial_scan_done);
  }
  else
  {
   enduser_setup_check_station_start();
  }

  if(enduser_setup_dns_start())
  {
    goto failed;
  }

  if(enduser_setup_http_start())
  {
    goto failed;
  }

  goto out;

failed:
  enduser_setup_stop(lua_getstate());
out:
  return 0;
}