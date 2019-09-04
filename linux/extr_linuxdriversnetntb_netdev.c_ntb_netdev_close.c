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
struct sk_buff {int dummy; } ;
struct ntb_netdev {int /*<<< orphan*/  tx_timer; int /*<<< orphan*/  qp; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntb_transport_link_down (int /*<<< orphan*/ ) ; 
 struct sk_buff* ntb_transport_rx_remove (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ntb_netdev_close(struct net_device *ndev)
{
	struct ntb_netdev *dev = netdev_priv(ndev);
	struct sk_buff *skb;
	int len;

	ntb_transport_link_down(dev->qp);

	while ((skb = ntb_transport_rx_remove(dev->qp, &len)))
		dev_kfree_skb(skb);

	del_timer_sync(&dev->tx_timer);

	return 0;
}