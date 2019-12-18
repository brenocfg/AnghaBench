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
typedef  int uint8_t ;
struct softap_config {char* ssid; int ssid_len; int channel; int max_connection; int beacon_interval; scalar_t__ ssid_hidden; int /*<<< orphan*/  authmode; } ;
struct TYPE_2__ {int softAPchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_OPEN ; 
 char* ENDUSER_SETUP_AP_SSID ; 
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  SOFTAP_IF ; 
 int /*<<< orphan*/  STATIONAP_MODE ; 
 int /*<<< orphan*/  memcpy (char**,char*,int) ; 
 int /*<<< orphan*/  memset (struct softap_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 TYPE_1__* state ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  wifi_get_macaddr (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wifi_set_opmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wifi_softap_set_config (struct softap_config*) ; 

__attribute__((used)) static void enduser_setup_ap_start(void)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_ap_start");

  struct softap_config cnf;
  memset(&(cnf), 0, sizeof(struct softap_config));

#ifndef ENDUSER_SETUP_AP_SSID
  #define ENDUSER_SETUP_AP_SSID "SetupGadget"
#endif

  char ssid[] = ENDUSER_SETUP_AP_SSID;
  int ssid_name_len = strlen(ssid);
  memcpy(&(cnf.ssid), ssid, ssid_name_len);

  uint8_t mac[6];
  wifi_get_macaddr(SOFTAP_IF, mac);
  cnf.ssid[ssid_name_len] = '_';
  sprintf(cnf.ssid + ssid_name_len + 1, "%02X%02X%02X", mac[3], mac[4], mac[5]);
  cnf.ssid_len = ssid_name_len + 7;
  cnf.channel = state == NULL? 1 : state->softAPchannel;
  cnf.authmode = AUTH_OPEN;
  cnf.ssid_hidden = 0;
  cnf.max_connection = 5;
  cnf.beacon_interval = 100;
  wifi_set_opmode(STATIONAP_MODE);
  wifi_softap_set_config(&cnf);

#if ENDUSER_SETUP_DEBUG_ENABLE
  char debuginfo[100];
  sprintf(debuginfo, "SSID: %s, CHAN: %d", cnf.ssid, cnf.channel);
  ENDUSER_SETUP_DEBUG(debuginfo);
#endif
}