#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
struct xenvif {TYPE_1__* queues; int /*<<< orphan*/  num_queues; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_5__ {int offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xenvif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_2__* xenvif_stats ; 

__attribute__((used)) static void xenvif_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 * data)
{
	struct xenvif *vif = netdev_priv(dev);
	unsigned int num_queues;
	int i;
	unsigned int queue_index;

	rcu_read_lock();
	num_queues = READ_ONCE(vif->num_queues);

	for (i = 0; i < ARRAY_SIZE(xenvif_stats); i++) {
		unsigned long accum = 0;
		for (queue_index = 0; queue_index < num_queues; ++queue_index) {
			void *vif_stats = &vif->queues[queue_index].stats;
			accum += *(unsigned long *)(vif_stats + xenvif_stats[i].offset);
		}
		data[i] = accum;
	}

	rcu_read_unlock();
}