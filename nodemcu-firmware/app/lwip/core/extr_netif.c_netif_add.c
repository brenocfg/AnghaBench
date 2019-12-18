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
typedef  scalar_t__ u8_t ;
struct netif {int flags; int /*<<< orphan*/ * name; struct netif* next; scalar_t__ loop_cnt_current; int /*<<< orphan*/ * addr_hint; int /*<<< orphan*/  input; scalar_t__ num; void* state; int /*<<< orphan*/ * loop_last; int /*<<< orphan*/ * loop_first; int /*<<< orphan*/ * igmp_mac_filter; int /*<<< orphan*/ * link_callback; int /*<<< orphan*/ * status_callback; int /*<<< orphan*/ * autoip; int /*<<< orphan*/ * dhcps_pcb; int /*<<< orphan*/ * dhcp; int /*<<< orphan*/  gw; int /*<<< orphan*/  netmask; int /*<<< orphan*/  ip_addr; } ;
typedef  int /*<<< orphan*/  netif_input_fn ;
typedef  scalar_t__ (* netif_init_fn ) (struct netif*) ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int NETIF_FLAG_IGMP ; 
 int /*<<< orphan*/  igmp_start (struct netif*) ; 
 int /*<<< orphan*/  ip_addr_debug_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_addr_set_zero (int /*<<< orphan*/ *) ; 
 struct netif* netif_list ; 
 int /*<<< orphan*/  netif_set_addr (struct netif*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_inc_iflist () ; 

struct netif *
netif_add(struct netif *netif, ip_addr_t *ipaddr, ip_addr_t *netmask,
  ip_addr_t *gw, void *state, netif_init_fn init, netif_input_fn input)
{
  static u8_t netifnum = 0;

  LWIP_ASSERT("No init function given", init != NULL);

  /* reset new interface configuration state */
  ip_addr_set_zero(&netif->ip_addr);
  ip_addr_set_zero(&netif->netmask);
  ip_addr_set_zero(&netif->gw);
  netif->flags = 0;
#if LWIP_DHCP
  /* netif not under DHCP control by default */
  netif->dhcp = NULL;
  netif->dhcps_pcb = NULL;
#endif /* LWIP_DHCP */
#if LWIP_AUTOIP
  /* netif not under AutoIP control by default */
  netif->autoip = NULL;
#endif /* LWIP_AUTOIP */
#if LWIP_NETIF_STATUS_CALLBACK
  netif->status_callback = NULL;
#endif /* LWIP_NETIF_STATUS_CALLBACK */
#if LWIP_NETIF_LINK_CALLBACK
  netif->link_callback = NULL;
#endif /* LWIP_NETIF_LINK_CALLBACK */
#if LWIP_IGMP
  netif->igmp_mac_filter = NULL;
#endif /* LWIP_IGMP */
#if ENABLE_LOOPBACK
  netif->loop_first = NULL;
  netif->loop_last = NULL;
#endif /* ENABLE_LOOPBACK */

  /* remember netif specific state information data */
  netif->state = state;
  netif->num = netifnum++;
  netif->input = input;
#if LWIP_NETIF_HWADDRHINT
  netif->addr_hint = NULL;
#endif /* LWIP_NETIF_HWADDRHINT*/
#if ENABLE_LOOPBACK && LWIP_LOOPBACK_MAX_PBUFS
  netif->loop_cnt_current = 0;
#endif /* ENABLE_LOOPBACK && LWIP_LOOPBACK_MAX_PBUFS */

  netif_set_addr(netif, ipaddr, netmask, gw);

  /* call user specified initialization function for netif */
  if (init(netif) != ERR_OK) {
    return NULL;
  }

  /* add this netif to the list */
  netif->next = netif_list;
  netif_list = netif;
  snmp_inc_iflist();

#if LWIP_IGMP
  /* start IGMP processing */
  if (netif->flags & NETIF_FLAG_IGMP) {
    igmp_start(netif);
  }
#endif /* LWIP_IGMP */

  LWIP_DEBUGF(NETIF_DEBUG, ("netif: added interface %c%c IP addr ",
    netif->name[0], netif->name[1]));
  ip_addr_debug_print(NETIF_DEBUG, ipaddr);
  LWIP_DEBUGF(NETIF_DEBUG, (" netmask "));
  ip_addr_debug_print(NETIF_DEBUG, netmask);
  LWIP_DEBUGF(NETIF_DEBUG, (" gw "));
  ip_addr_debug_print(NETIF_DEBUG, gw);
  LWIP_DEBUGF(NETIF_DEBUG, ("\n"));
  return netif;
}