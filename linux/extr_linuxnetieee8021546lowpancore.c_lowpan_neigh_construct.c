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
struct net_device {int dummy; } ;
struct neighbour {int dummy; } ;
struct lowpan_802154_neigh {int /*<<< orphan*/  short_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_ADDR_SHORT_UNSPEC ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct lowpan_802154_neigh* lowpan_802154_neigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neighbour_priv (struct neighbour*) ; 

__attribute__((used)) static int lowpan_neigh_construct(struct net_device *dev, struct neighbour *n)
{
	struct lowpan_802154_neigh *neigh = lowpan_802154_neigh(neighbour_priv(n));

	/* default no short_addr is available for a neighbour */
	neigh->short_addr = cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC);
	return 0;
}