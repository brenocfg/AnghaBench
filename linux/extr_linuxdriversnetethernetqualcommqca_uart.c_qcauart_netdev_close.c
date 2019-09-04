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
struct qcauart {int /*<<< orphan*/  lock; scalar_t__ tx_left; int /*<<< orphan*/  tx_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct qcauart* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qcauart_netdev_close(struct net_device *dev)
{
	struct qcauart *qca = netdev_priv(dev);

	netif_stop_queue(dev);
	flush_work(&qca->tx_work);

	spin_lock_bh(&qca->lock);
	qca->tx_left = 0;
	spin_unlock_bh(&qca->lock);

	return 0;
}