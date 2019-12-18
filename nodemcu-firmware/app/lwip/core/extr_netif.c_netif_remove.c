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
struct netif {int flags; struct netif* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 int NETIF_FLAG_IGMP ; 
 int /*<<< orphan*/  igmp_stop (struct netif*) ; 
 struct netif* netif_default ; 
 scalar_t__ netif_is_up (struct netif*) ; 
 struct netif* netif_list ; 
 int /*<<< orphan*/  netif_set_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_set_down (struct netif*) ; 
 int /*<<< orphan*/  snmp_dec_iflist () ; 
 int /*<<< orphan*/  snmp_delete_ipaddridx_tree (struct netif*) ; 

void
netif_remove(struct netif *netif)
{
  if (netif == NULL) {
    return;
  }

#if LWIP_IGMP
  /* stop IGMP processing */
  if (netif->flags & NETIF_FLAG_IGMP) {
    igmp_stop(netif);
  }
#endif /* LWIP_IGMP */
  if (netif_is_up(netif)) {
    /* set netif down before removing (call callback function) */
    netif_set_down(netif);
  }

  snmp_delete_ipaddridx_tree(netif);

  /*  is it the first netif? */
  if (netif_list == netif) {
    netif_list = netif->next;
  } else {
    /*  look for netif further down the list */
    struct netif * tmpNetif;
    for (tmpNetif = netif_list; tmpNetif != NULL; tmpNetif = tmpNetif->next) {
      if (tmpNetif->next == netif) {
        tmpNetif->next = netif->next;
        break;
      }
    }
    if (tmpNetif == NULL)
      return; /*  we didn't find any netif today */
  }
  snmp_dec_iflist();
  /* this netif is default? */
  if (netif_default == netif) {
    /* reset default netif */
    netif_set_default(NULL);
  }
  LWIP_DEBUGF( NETIF_DEBUG, ("netif_remove: removed netif\n") );
}