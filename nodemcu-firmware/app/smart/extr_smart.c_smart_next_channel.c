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
struct TYPE_2__ {int /*<<< orphan*/  password; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_MAP_NUM ; 
#define  MAX_CHANNEL 128 
 int /*<<< orphan*/  NODE_ERR (char*,int) ; 
 int PWD_BIT_MAX ; 
 int PWD_NIBBLE_MAX ; 
 int SSID_BIT_MAX ; 
 int SSID_NIBBLE_MAX ; 
 int /*<<< orphan*/  TIME_OUT_PER_CHANNEL ; 
 int /*<<< orphan*/  am ; 
 int cur_channel ; 
 int /*<<< orphan*/  got_password ; 
 int /*<<< orphan*/  got_ssid ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  password_nibble ; 
 int /*<<< orphan*/  reset_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_disable () ; 
 int /*<<< orphan*/  smart_enable () ; 
 int /*<<< orphan*/  smart_timer ; 
 int /*<<< orphan*/  ssid_nibble ; 
 TYPE_1__* sta_conf ; 
 int /*<<< orphan*/  wifi_set_channel (int) ; 

void smart_next_channel(){
  smart_disable();
  switch(cur_channel){
    case 1:
      cur_channel = MAX_CHANNEL;
      break;
    case 2:
    case 3:
    case 4:
      cur_channel++;
      break;
    case 5:
      cur_channel = 7;
      break;
    case 6:
      cur_channel = 1;
      break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      cur_channel++;
      break;
    case 13:
      cur_channel = 6;
      break;
    case MAX_CHANNEL:
      cur_channel = 2;
      break;
    default:
      cur_channel = 6;
      break;
  }

  NODE_ERR("switch to channel %d\n", cur_channel);
  wifi_set_channel(cur_channel);
  reset_map(am, ADDR_MAP_NUM);
  memset(sta_conf->ssid, 0, sizeof(sta_conf->ssid));
  memset(sta_conf->password, 0, sizeof(sta_conf->password));

  memset(got_ssid, 0, SSID_BIT_MAX);
  memset(got_password, 0, PWD_BIT_MAX);

  memset(ssid_nibble, 0, SSID_NIBBLE_MAX);
  memset(password_nibble, 0, PWD_NIBBLE_MAX);

  os_timer_disarm(&smart_timer);
  os_timer_arm(&smart_timer, TIME_OUT_PER_CHANNEL, 0);   // no repeat

  smart_enable();
}