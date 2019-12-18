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
struct chnl_net {int /*<<< orphan*/  list_field; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct chnl_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  robust_list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chnl_net_uninit(struct net_device *dev)
{
	struct chnl_net *priv;
	ASSERT_RTNL();
	priv = netdev_priv(dev);
	robust_list_del(&priv->list_field);
}