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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ntb_netdev {int /*<<< orphan*/  qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct ntb_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ntb_netdev_maybe_stop_tx (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntb_transport_tx_enqueue (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_stop ; 

__attribute__((used)) static netdev_tx_t ntb_netdev_start_xmit(struct sk_buff *skb,
					 struct net_device *ndev)
{
	struct ntb_netdev *dev = netdev_priv(ndev);
	int rc;

	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	rc = ntb_transport_tx_enqueue(dev->qp, skb, skb->data, skb->len);
	if (rc)
		goto err;

	/* check for next submit */
	ntb_netdev_maybe_stop_tx(ndev, dev->qp, tx_stop);

	return NETDEV_TX_OK;

err:
	ndev->stats.tx_dropped++;
	ndev->stats.tx_errors++;
	return NETDEV_TX_BUSY;
}