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
struct netdev_tc_txq {unsigned int offset; unsigned int count; } ;
struct net_device {struct netdev_tc_txq* tc_to_txq; scalar_t__ num_tc; } ;

/* Variables and functions */
 int TC_BITMASK ; 
 int netdev_get_prio_tc_map (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_prio_tc_map (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static void netif_setup_tc(struct net_device *dev, unsigned int txq)
{
	int i;
	struct netdev_tc_txq *tc = &dev->tc_to_txq[0];

	/* If TC0 is invalidated disable TC mapping */
	if (tc->offset + tc->count > txq) {
		pr_warn("Number of in use tx queues changed invalidating tc mappings. Priority traffic classification disabled!\n");
		dev->num_tc = 0;
		return;
	}

	/* Invalidated prio to tc mappings set to TC0 */
	for (i = 1; i < TC_BITMASK + 1; i++) {
		int q = netdev_get_prio_tc_map(dev, i);

		tc = &dev->tc_to_txq[q];
		if (tc->offset + tc->count > txq) {
			pr_warn("Number of in use tx queues changed. Priority %i to tc mapping %i is no longer valid. Setting map to 0\n",
				i, q);
			netdev_set_prio_tc_map(dev, i, 0);
		}
	}
}