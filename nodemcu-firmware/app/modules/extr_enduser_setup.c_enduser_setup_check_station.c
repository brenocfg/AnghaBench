#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct ip_info {TYPE_1__ ip; } ;
struct TYPE_4__ {int softAPchannel; int lastStationStatus; int success; int callbackDone; int /*<<< orphan*/  shutdown_timer; scalar_t__ connecting; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOFTAP_MODE ; 
 int /*<<< orphan*/  STATION_IF ; 
 int /*<<< orphan*/  SWTIMER_REG_CB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWTIMER_RESUME ; 
 int /*<<< orphan*/  enduser_setup_ap_start () ; 
 int /*<<< orphan*/  enduser_setup_check_station_stop () ; 
 int /*<<< orphan*/  enduser_setup_connected_callback () ; 
 int /*<<< orphan*/  enduser_setup_stop_callback ; 
 int /*<<< orphan*/  ipaddr ; 
 int /*<<< orphan*/  manual ; 
 int /*<<< orphan*/  memset (struct ip_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_timer_setfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 TYPE_2__* state ; 
 int wifi_get_channel () ; 
 int /*<<< orphan*/  wifi_get_ip_info (int /*<<< orphan*/ ,struct ip_info*) ; 
 int /*<<< orphan*/  wifi_set_opmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_station_disconnect () ; 
 int wifi_station_get_connect_status () ; 

__attribute__((used)) static void enduser_setup_check_station(void *p)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_check_station");

  (void)p;
  struct ip_info ip;
  memset(&ip, 0, sizeof(struct ip_info));

  wifi_get_ip_info(STATION_IF, &ip);

  int i;
  char has_ip = 0;
  for (i = 0; i < sizeof(struct ip_info); ++i)
  {
    has_ip |= ((char *) &ip)[i];
  }

  uint8_t currChan = wifi_get_channel();

  if (has_ip == 0)
  {
    /* No IP Address yet, so check the reported status */
    uint8_t curr_status = wifi_station_get_connect_status();
    char buf[20];
    sprintf(buf, "status=%d,chan=%d", curr_status, currChan);
    ENDUSER_SETUP_DEBUG(buf);

    if (curr_status == 2 || curr_status == 3 || curr_status == 4)
    {
      state->connecting = 0;

      /* If the status is an error status and the channel changed, then cache the
       * status to state since the Station won't be able to report the same status
       * after switching the channel back to the SoftAP's
       */
      if (currChan != state->softAPchannel) {
        state->lastStationStatus = curr_status;

        ENDUSER_SETUP_DEBUG("Turning off Station due to different channel than AP");

        wifi_station_disconnect();
        wifi_set_opmode(SOFTAP_MODE);
        enduser_setup_ap_start();
      }
   }
   return;
  }

  sprintf (ipaddr, "%d.%d.%d.%d", IP2STR(&ip.ip.addr));

  state->success = 1;
  state->lastStationStatus = 5; /*  We have an IP Address, so the status is 5 (as of SDK 1.5.1) */
  state->connecting = 0;

#if ENDUSER_SETUP_DEBUG_ENABLE
  char debuginfo[100];
  sprintf(debuginfo, "AP_CHAN: %d, STA_CHAN: %d", state->softAPchannel, currChan);
  ENDUSER_SETUP_DEBUG(debuginfo);
#endif

  if (currChan == state->softAPchannel)
  {
    enduser_setup_connected_callback();
    state->callbackDone = 1;
  }
  else
  {
    ENDUSER_SETUP_DEBUG("Turning off Station due to different channel than AP");
    wifi_station_disconnect();
    wifi_set_opmode(SOFTAP_MODE);
    enduser_setup_ap_start();
  }

  enduser_setup_check_station_stop();

  /* Trigger shutdown, but allow time for HTTP client to fetch last status. */
  if (!manual)
  {
    os_timer_setfn(&(state->shutdown_timer), enduser_setup_stop_callback, NULL);
    SWTIMER_REG_CB(enduser_setup_stop_callback, SWTIMER_RESUME);
      //The function enduser_setup_stop_callback frees services and resources used by enduser setup.
      //My guess: Since it would lead to a memory leak, it's probably best to resume this timer.
    os_timer_arm(&(state->shutdown_timer), 10*1000, FALSE);
  }
}