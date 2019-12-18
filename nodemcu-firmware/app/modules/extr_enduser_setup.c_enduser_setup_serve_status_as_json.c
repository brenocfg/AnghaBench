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
struct tcp_pcb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct ip_info {TYPE_1__ ip; } ;
struct TYPE_4__ {scalar_t__ lastStationStatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int IP2STR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NUMLEN (int) ; 
 int /*<<< orphan*/  STATION_IF ; 
 int /*<<< orphan*/  enduser_setup_http_serve_header (struct tcp_pcb*,char*,int) ; 
 char* ipaddr ; 
 int sprintf (char*,char const*,...) ; 
 TYPE_2__* state ; 
 int strlen (char const*) ; 
 int system_get_chip_id () ; 
 int /*<<< orphan*/  wifi_get_ip_info (int /*<<< orphan*/ ,struct ip_info*) ; 
 int wifi_station_get_connect_status () ; 

__attribute__((used)) static void enduser_setup_serve_status_as_json (struct tcp_pcb *http_client)
{
  ENDUSER_SETUP_DEBUG("enduser_setup_serve_status_as_json");

  /* If the station is currently shut down because of wi-fi channel issue, use the cached status */
  uint8_t curr_status = state->lastStationStatus > 0 ? state->lastStationStatus : wifi_station_get_connect_status ();

  char json_payload[64];

  struct ip_info ip_info;

  if (curr_status == 5)
  {
    wifi_get_ip_info(STATION_IF , &ip_info);
    /* If IP address not yet available, get now */
    if (strlen(ipaddr) == 0)
    {
      sprintf(ipaddr, "%d.%d.%d.%d", IP2STR(&ip_info.ip.addr));
    }
    sprintf(json_payload, "{\"deviceid\":\"%s\", \"status\":%d}", ipaddr, curr_status);
  }
  else
  {
    sprintf(json_payload, "{\"deviceid\":\"%06X\", \"status\":%d}", system_get_chip_id(), curr_status);
  }

  const char fmt[] =
    "HTTP/1.1 200 OK\r\n"
    "Cache-Control: no-cache\r\n"
    "Connection: close\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s";

  int len = strlen(json_payload);
  char buf[strlen(fmt) + NUMLEN(len) + len - 4];
  len = sprintf (buf, fmt, len, json_payload);
  enduser_setup_http_serve_header (http_client, buf, len);
}