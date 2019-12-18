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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_D2 ; 
#define  IP_LINK_DOWN 129 
#define  IP_LINK_UP 128 
 int /*<<< orphan*/  LEDWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UARTprintf (char*,...) ; 
 int /*<<< orphan*/  g_mgr ; 
 int /*<<< orphan*/  ipaddr_ntoa (int /*<<< orphan*/  const*) ; 
 int lwIPLocalIPAddrGet () ; 
 int /*<<< orphan*/  mg_mgr_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void lwIPHostTimerHandler(void) {
  static uint32_t old_ip = IP_LINK_DOWN;
  uint32_t ip = lwIPLocalIPAddrGet();
  if (ip != old_ip) {
    switch (ip) {
      case IP_LINK_DOWN: {
        UARTprintf("Link down.\r\n");
        LEDWrite(CLP_D2, 0);
        break;
      }
      case IP_LINK_UP: {
        UARTprintf("Link up.\r\n");
        LEDWrite(CLP_D2, 0);
        break;
      }
      default: {
        UARTprintf("IP: http://%s/\r\n", ipaddr_ntoa((const ip_addr_t *) &ip));
        LEDWrite(CLP_D2, CLP_D2);
        break;
      }
    }
    old_ip = ip;
  }

  mg_mgr_poll(&g_mgr, 0);
}