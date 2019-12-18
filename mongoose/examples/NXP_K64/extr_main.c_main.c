#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8_t ;
struct netif {int /*<<< orphan*/  ip_addr; TYPE_1__* dhcp; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {int dummy; } ;
struct mg_bind_opts {char const** error_string; } ;
typedef  int /*<<< orphan*/  ip_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  CESR; } ;
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_2__ MPU_Type ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_BootClockRUN () ; 
 int /*<<< orphan*/  BOARD_InitDebugConsole () ; 
 int /*<<< orphan*/  BOARD_InitPins () ; 
 scalar_t__ DHCP_BOUND ; 
 int /*<<< orphan*/  LED_GREEN_OFF () ; 
 int /*<<< orphan*/  LED_GREEN_ON () ; 
 int /*<<< orphan*/  LED_RED_OFF () ; 
 int /*<<< orphan*/  LED_RED_ON () ; 
 TYPE_2__* MPU ; 
 int /*<<< orphan*/  MPU_CESR_VLD_MASK ; 
 int /*<<< orphan*/  STATIC_GW ; 
 int /*<<< orphan*/  STATIC_IP ; 
 int /*<<< orphan*/  STATIC_NM ; 
 int /*<<< orphan*/  dhcp_start (struct netif*) ; 
 int /*<<< orphan*/  ethernet_input ; 
 int /*<<< orphan*/  ethernetif_init ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  gpio_init () ; 
 int /*<<< orphan*/  ipaddr_aton (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* ipaddr_ntoa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwip_init () ; 
 struct mg_connection* mg_bind_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,struct mg_bind_opts) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  netif_add (struct netif*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_default (struct netif*) ; 
 int /*<<< orphan*/  netif_set_up (struct netif*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sys_check_timeouts () ; 

int main(void) {
  struct netif eth0;
  MPU_Type *base = MPU;
  BOARD_InitPins();
  BOARD_BootClockRUN();
  BOARD_InitDebugConsole();
  /* Disable MPU. */
  base->CESR &= ~MPU_CESR_VLD_MASK;
  lwip_init();
  gpio_init();
  LED_RED_ON();
  printf("Waiting for link...\r\n");
#if USE_DHCP
  netif_add(&eth0, NULL, NULL, NULL, NULL, ethernetif_init, ethernet_input);
  printf("Waiting for DHCP...\r\n");
  LED_GREEN_ON();
  dhcp_start(&eth0);
  u8_t os = 0xff, ds;
  do {
    ds = eth0.dhcp->state;
    if (ds != os) {
      printf("  DHCP state: %d\r\n", ds);
      os = ds;
    }
    sys_check_timeouts();
  } while (ds != DHCP_BOUND);
  printf("DHCP bound.\r\n");
#else
  ip_addr_t ip, nm, gw;
  if (!ipaddr_aton(STATIC_IP, &ip) || !ipaddr_aton(STATIC_NM, &nm) ||
      !ipaddr_aton(STATIC_GW, &gw)) {
    printf("Invalid static IP configuration.\r\n");
    return 1;
  } else {
    netif_add(&eth0, &ip, &nm, &gw, NULL, ethernetif_init, ethernet_input);
    netif_set_up(&eth0);
  }
#endif
  netif_set_default(&eth0);
  printf("Setting up HTTP server...\r\n");

  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  const char *err;
  struct mg_bind_opts opts = {};
  opts.error_string = &err;
  struct mg_connection *nc = mg_bind_opt(&mgr, "80", ev_handler, opts);
  if (nc == NULL) {
    printf("Failed to create listener: %s\r\n", err);
    LED_RED_ON();
    LED_GREEN_OFF();
    return 1;
  }
  mg_set_protocol_http_websocket(nc);
  printf("Server address: http://%s/\r\n", ipaddr_ntoa(&eth0.ip_addr));
  LED_RED_OFF();
  LED_GREEN_ON();

  while (1) {
    sys_check_timeouts();
    mg_mgr_poll(&mgr, 0);
  }

  return 0;
}