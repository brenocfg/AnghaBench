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
typedef  scalar_t__ u16 ;
struct virtnet_info {scalar_t__ max_queue_pairs; TYPE_1__* rq; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;
struct TYPE_2__ {scalar_t__ xdp_prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int _virtnet_set_queues (struct virtnet_info*,scalar_t__) ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  virtnet_set_affinity (struct virtnet_info*) ; 

__attribute__((used)) static int virtnet_set_channels(struct net_device *dev,
				struct ethtool_channels *channels)
{
	struct virtnet_info *vi = netdev_priv(dev);
	u16 queue_pairs = channels->combined_count;
	int err;

	/* We don't support separate rx/tx channels.
	 * We don't allow setting 'other' channels.
	 */
	if (channels->rx_count || channels->tx_count || channels->other_count)
		return -EINVAL;

	if (queue_pairs > vi->max_queue_pairs || queue_pairs == 0)
		return -EINVAL;

	/* For now we don't support modifying channels while XDP is loaded
	 * also when XDP is loaded all RX queues have XDP programs so we only
	 * need to check a single RX queue.
	 */
	if (vi->rq[0].xdp_prog)
		return -EINVAL;

	get_online_cpus();
	err = _virtnet_set_queues(vi, queue_pairs);
	if (!err) {
		netif_set_real_num_tx_queues(dev, queue_pairs);
		netif_set_real_num_rx_queues(dev, queue_pairs);

		virtnet_set_affinity(vi);
	}
	put_online_cpus();

	return err;
}