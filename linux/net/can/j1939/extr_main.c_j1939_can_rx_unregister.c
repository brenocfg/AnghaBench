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
struct net_device {int dummy; } ;
struct j1939_priv {struct net_device* ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  J1939_CAN_ID ; 
 int /*<<< orphan*/  J1939_CAN_MASK ; 
 int /*<<< orphan*/  can_rx_unregister (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct j1939_priv*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  j1939_can_recv ; 
 int /*<<< orphan*/  j1939_priv_put (struct j1939_priv*) ; 

__attribute__((used)) static void j1939_can_rx_unregister(struct j1939_priv *priv)
{
	struct net_device *ndev = priv->ndev;

	can_rx_unregister(dev_net(ndev), ndev, J1939_CAN_ID, J1939_CAN_MASK,
			  j1939_can_recv, priv);

	j1939_priv_put(priv);
}