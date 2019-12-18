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
typedef  int uint32_t ;
struct netif {TYPE_1__* dhcp; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Board_LED_Set (int,int) ; 
 int /*<<< orphan*/  Chip_ENET_Set100Mbps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Chip_ENET_Set10Mbps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Chip_ENET_SetFullDuplex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Chip_ENET_SetHalfDuplex (int /*<<< orphan*/ ) ; 
 scalar_t__ DHCP_BOUND ; 
 int /*<<< orphan*/  LPC_ETHERNET ; 
 int PHY_LINK_CHANGED ; 
 int PHY_LINK_CONNECTED ; 
 int PHY_LINK_FULLDUPLX ; 
 int PHY_LINK_SPEED100 ; 
 int lpcPHYStsPoll () ; 
 int /*<<< orphan*/  lpc_enetif_input (struct netif*) ; 
 int /*<<< orphan*/  lpc_tx_reclaim (struct netif*) ; 
 int /*<<< orphan*/  netif_set_link_down (struct netif*) ; 
 int /*<<< orphan*/  netif_set_link_up (struct netif*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void handle_eth(struct netif *eth_if) {
  /* PHY link status. */
  uint32_t status = lpcPHYStsPoll();

  if (status & PHY_LINK_CHANGED) {
    if (status & PHY_LINK_CONNECTED) {
      Board_LED_Set(0, true);

      if (status & PHY_LINK_SPEED100) {
        Chip_ENET_Set100Mbps(LPC_ETHERNET);
      } else {
        Chip_ENET_Set10Mbps(LPC_ETHERNET);
      }
      if (status & PHY_LINK_FULLDUPLX) {
        Chip_ENET_SetFullDuplex(LPC_ETHERNET);
      } else {
        Chip_ENET_SetHalfDuplex(LPC_ETHERNET);
      }

      netif_set_link_up(eth_if);
      printf("Link up\r\n");
    } else {
      Board_LED_Set(0, false);
      netif_set_link_down(eth_if);
      printf("Link down\r\n");
    }
  }

  Board_LED_Set(1, (eth_if->dhcp->state == DHCP_BOUND));

  /* Handle packets as part of this loop, not in the IRQ handler */
  lpc_enetif_input(eth_if);

  /* Free TX buffers that are done sending */
  lpc_tx_reclaim(eth_if);
}