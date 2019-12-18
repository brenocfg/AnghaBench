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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mg_connection {int dummy; } ;
struct mg_bind_opts {char const** error_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLP_D1 ; 
 int /*<<< orphan*/  CLP_D1_PIN ; 
 int /*<<< orphan*/  CLP_D1_PORT ; 
 int /*<<< orphan*/  CLP_D2 ; 
 int /*<<< orphan*/  CLP_D2_PIN ; 
 int /*<<< orphan*/  CLP_D2_PORT ; 
 int /*<<< orphan*/  IPADDR_USE_DHCP ; 
 int /*<<< orphan*/  LEDWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_FlashUserGet (int*,int*) ; 
 int /*<<< orphan*/  MAP_GPIOPinTypeGPIOOutput (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAP_SysCtlClockFreqSet (int,int) ; 
 int /*<<< orphan*/  MAP_SysTickEnable () ; 
 int /*<<< orphan*/  MAP_SysTickIntEnable () ; 
 int /*<<< orphan*/  MAP_SysTickPeriodSet (int) ; 
 int /*<<< orphan*/  PinoutSet (int,int) ; 
 int SYSCTL_CFG_VCO_480 ; 
 int /*<<< orphan*/  SYSCTL_MOSC_HIGHFREQ ; 
 int SYSCTL_OSC_MAIN ; 
 int SYSCTL_USE_PLL ; 
 int SYSCTL_XTAL_25MHZ ; 
 int SYSTICKHZ ; 
 int /*<<< orphan*/  SysCtlMOSCConfigSet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UARTStdioConfig (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  UARTprintf (char*,...) ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  g_mgr ; 
 int /*<<< orphan*/  lwIPInit (int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_bind_opt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct mg_bind_opts) ; 
 int /*<<< orphan*/  mg_mgr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 

int main(void) {
  //
  // Make sure the main oscillator is enabled because this is required by
  // the PHY.  The system must have a 25MHz crystal attached to the OSC
  // pins. The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
  // frequency is 10MHz or higher.
  //
  SysCtlMOSCConfigSet(SYSCTL_MOSC_HIGHFREQ);

  // Run from the PLL at 120 MHz.
  uint32_t sys_clk =
      MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                              SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                             120000000);

  // Configure the device pins.
  PinoutSet(true, false);

  // Configure UART.
  UARTStdioConfig(0, 115200, sys_clk);
  UARTprintf("Mongoose example\n\n");

  // Configure board's LEDs: D2 is on when IP has been acquired,
  // D1 is toggled on every HTTP request.
  MAP_GPIOPinTypeGPIOOutput(CLP_D1_PORT, CLP_D1_PIN);
  MAP_GPIOPinTypeGPIOOutput(CLP_D2_PORT, CLP_D2_PIN);
  LEDWrite(CLP_D1, 0);
  LEDWrite(CLP_D2, 0);

  //
  // Configure the hardware MAC address for Ethernet Controller filtering of
  // incoming packets.  The MAC address will be stored in the non-volatile
  // USER0 and USER1 registers.
  //
  uint32_t u0, u1;
  MAP_FlashUserGet(&u0, &u1);
  uint8_t mac[6];
  mac[0] = ((u0 >> 0) & 0xff);
  mac[1] = ((u0 >> 8) & 0xff);
  mac[2] = ((u0 >> 16) & 0xff);
  mac[3] = ((u1 >> 0) & 0xff);
  mac[4] = ((u1 >> 8) & 0xff);
  mac[5] = ((u1 >> 16) & 0xff);

  // Initialize the lwIP library, using DHCP.
  lwIPInit(sys_clk, mac, 0, 0, 0, IPADDR_USE_DHCP);

  // Configure Mongoose, create an HTTP listener.
  mg_mgr_init(&g_mgr, NULL);
  const char *err;
  struct mg_bind_opts opts = {};
  opts.error_string = &err;
  struct mg_connection *nc = mg_bind_opt(&g_mgr, "80", ev_handler, opts);
  if (nc == NULL) {
    UARTprintf("Failed to create listener: %s\r\n", err);
    return 1;
  }
  mg_set_protocol_http_websocket(nc);

  // Configure SysTick for a periodic interrupt.
  MAP_SysTickPeriodSet(sys_clk / SYSTICKHZ);
  MAP_SysTickEnable();
  MAP_SysTickIntEnable();

  // Loop forever.  All the work is done in interrupt handlers.
  while (true) {
  }
}