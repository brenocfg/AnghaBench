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
struct ethsw_port_priv {int /*<<< orphan*/ * bridge_dev; } ;

/* Variables and functions */
 int ethsw_port_set_flood (struct ethsw_port_priv*,int /*<<< orphan*/ ) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int port_bridge_leave(struct net_device *netdev)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	int err;

	/* Disable flooding */
	err = ethsw_port_set_flood(port_priv, 0);
	if (!err)
		port_priv->bridge_dev = NULL;

	return err;
}