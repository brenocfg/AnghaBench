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
typedef  int /*<<< orphan*/  os_timer_func_t ;

/* Variables and functions */
 int ADDR_MAP_NUM ; 
 scalar_t__ NULL_MODE ; 
 scalar_t__ STATIONAP_MODE ; 
 int /*<<< orphan*/  STATION_CHECK_TIME ; 
 scalar_t__ STATION_MODE ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 scalar_t__ alldone ; 
 int /*<<< orphan*/ ** am ; 
 int /*<<< orphan*/  cur_channel ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * got_password ; 
 int /*<<< orphan*/ * got_ssid ; 
 int /*<<< orphan*/ * matched ; 
 scalar_t__ mode ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * password_nibble ; 
 int /*<<< orphan*/  smart_disable () ; 
 int /*<<< orphan*/  smart_timer ; 
 int /*<<< orphan*/ * ssid_nibble ; 
 int /*<<< orphan*/ * sta_conf ; 
 scalar_t__ station_check_connect ; 
 scalar_t__ wifi_get_opmode () ; 
 int /*<<< orphan*/  wifi_set_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_set_opmode (scalar_t__) ; 
 int /*<<< orphan*/  wifi_station_connect () ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 
 int /*<<< orphan*/  wifi_station_set_auto_connect (int) ; 
 int /*<<< orphan*/  wifi_station_set_config (int /*<<< orphan*/ *) ; 

void smart_end(){
  int i;
  os_timer_disarm(&smart_timer);
  smart_disable();
  wifi_set_channel(cur_channel);

  if(NULL_MODE != mode){
    wifi_set_opmode(mode);
  } else {
    wifi_set_opmode(STATION_MODE);
  }

  mode = wifi_get_opmode();

  if(sta_conf && alldone){
    if( (STATION_MODE == mode) || (mode == STATIONAP_MODE) ){
      wifi_station_set_config(sta_conf);
      wifi_station_set_auto_connect(true);
      wifi_station_disconnect();
      wifi_station_connect();

      os_timer_disarm(&smart_timer);
      os_timer_setfn(&smart_timer, (os_timer_func_t *)station_check_connect, (void *)1);
      SWTIMER_REG_CB(station_check_connect, SWTIMER_RESUME);
        //the function station_check_connect continues the Smart config process and fires the developers callback upon successful connection to the access point.
        //If this function manages to get suspended, I think it would be fine to resume the timer.
      os_timer_arm(&smart_timer, STATION_CHECK_TIME, 0);   // no repeat
    }
  }

  for (i = 0; i < ADDR_MAP_NUM; ++i)
  {
    if(am[i]){
      free(am[i]);
      am[i] = NULL;
    }
    matched = NULL;
  }

  if(sta_conf){
    free(sta_conf);
    sta_conf = NULL;
  }

  if(got_password){
    free(got_password);
    got_password = NULL;
  }

  if(got_ssid){
    free(got_ssid);
    got_ssid = NULL;
  }

  if(password_nibble){
    free(password_nibble);
    password_nibble = NULL;
  }

  if(ssid_nibble){
    free(ssid_nibble);
    ssid_nibble = NULL;
  }
  // system_restart();   // restart to enable the mode
}