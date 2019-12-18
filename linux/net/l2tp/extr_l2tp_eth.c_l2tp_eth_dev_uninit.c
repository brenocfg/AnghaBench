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
struct l2tp_eth_sess {int /*<<< orphan*/  dev; } ;
struct l2tp_eth {int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct l2tp_eth_sess* l2tp_session_priv (int /*<<< orphan*/ ) ; 
 struct l2tp_eth* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void l2tp_eth_dev_uninit(struct net_device *dev)
{
	struct l2tp_eth *priv = netdev_priv(dev);
	struct l2tp_eth_sess *spriv;

	spriv = l2tp_session_priv(priv->session);
	RCU_INIT_POINTER(spriv->dev, NULL);
	/* No need for synchronize_net() here. We're called by
	 * unregister_netdev*(), which does the synchronisation for us.
	 */
}