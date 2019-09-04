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
struct netif {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 struct netif* netif_default ; 
 int /*<<< orphan*/  snmp_delete_iprteidx_tree (int,struct netif*) ; 
 int /*<<< orphan*/  snmp_insert_iprteidx_tree (int,struct netif*) ; 

void
netif_set_default(struct netif *netif)
{
  if (netif == NULL) {
    /* remove default route */
    snmp_delete_iprteidx_tree(1, netif);
  } else {
    /* install default route */
    snmp_insert_iprteidx_tree(1, netif);
  }
  netif_default = netif;
  LWIP_DEBUGF(NETIF_DEBUG, ("netif: setting default interface %c%c\n",
           netif ? netif->name[0] : '\'', netif ? netif->name[1] : '\''));
}