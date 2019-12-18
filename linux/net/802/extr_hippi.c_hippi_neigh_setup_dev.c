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
struct net_device {int dummy; } ;
struct neigh_parms {TYPE_1__* tbl; } ;
struct TYPE_2__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  MCAST_PROBES ; 
 int /*<<< orphan*/  NEIGH_VAR_INIT (struct neigh_parms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCAST_PROBES ; 

int hippi_neigh_setup_dev(struct net_device *dev, struct neigh_parms *p)
{
	/* Never send broadcast/multicast ARP messages */
	NEIGH_VAR_INIT(p, MCAST_PROBES, 0);

	/* In IPv6 unicast probes are valid even on NBMA,
	* because they are encapsulated in normal IPv6 protocol.
	* Should be a generic flag.
	*/
	if (p->tbl->family != AF_INET6)
		NEIGH_VAR_INIT(p, UCAST_PROBES, 0);
	return 0;
}