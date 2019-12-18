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
struct chnl_net {int /*<<< orphan*/  chnl; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  CAIF_DISCONNECTED ; 
 int /*<<< orphan*/  caif_disconnect_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct chnl_net* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int chnl_net_stop(struct net_device *dev)
{
	struct chnl_net *priv;

	ASSERT_RTNL();
	priv = netdev_priv(dev);
	priv->state = CAIF_DISCONNECTED;
	caif_disconnect_client(dev_net(dev), &priv->chnl);
	return 0;
}