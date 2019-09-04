#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_3__ {int offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 void* netdev_priv (struct net_device*) ; 
 TYPE_1__* xennet_stats ; 

__attribute__((used)) static void xennet_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 * data)
{
	void *np = netdev_priv(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(xennet_stats); i++)
		data[i] = atomic_read((atomic_t *)(np + xennet_stats[i].offset));
}