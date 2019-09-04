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
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; } ;
struct bigmac {int /*<<< orphan*/  bregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  bigmac_get_counters (struct bigmac*,int /*<<< orphan*/ ) ; 
 struct bigmac* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *bigmac_get_stats(struct net_device *dev)
{
	struct bigmac *bp = netdev_priv(dev);

	bigmac_get_counters(bp, bp->bregs);
	return &dev->stats;
}