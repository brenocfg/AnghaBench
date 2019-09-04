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
typedef  int /*<<< orphan*/  uint8 ;
struct station_config {int dummy; } ;
typedef  int /*<<< orphan*/  sta_conf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct station_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 
 int /*<<< orphan*/  wifi_station_set_auto_connect (int /*<<< orphan*/ ) ; 
 int wifi_station_set_config (struct station_config*) ; 
 int wifi_station_set_config_current (struct station_config*) ; 

__attribute__((used)) static int wifi_station_clear_config ( lua_State* L )
{
  struct station_config sta_conf;
  bool auto_connect=true;
  bool save_to_flash=true;

  memset(&sta_conf, 0, sizeof(sta_conf));

  wifi_station_disconnect();

  bool config_success;
  if(save_to_flash)
  {
    config_success = wifi_station_set_config(&sta_conf);
  }
  else
  {
    config_success = wifi_station_set_config_current(&sta_conf);
  }

  wifi_station_set_auto_connect((uint8)0);

  lua_pushboolean(L, config_success);
  return 1;
}