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
struct qcauart {scalar_t__ rx_skb; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 struct qcauart* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void qcauart_netdev_uninit(struct net_device *dev)
{
	struct qcauart *qca = netdev_priv(dev);

	if (qca->rx_skb)
		dev_kfree_skb(qca->rx_skb);
}