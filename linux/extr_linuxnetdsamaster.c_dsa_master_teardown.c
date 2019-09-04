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
struct net_device {int /*<<< orphan*/ * dsa_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_master_ethtool_teardown (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

void dsa_master_teardown(struct net_device *dev)
{
	dsa_master_ethtool_teardown(dev);

	dev->dsa_ptr = NULL;

	/* If we used a tagging format that doesn't have an ethertype
	 * field, make sure that all packets from this point get sent
	 * without the tag and go through the regular receive path.
	 */
	wmb();
}