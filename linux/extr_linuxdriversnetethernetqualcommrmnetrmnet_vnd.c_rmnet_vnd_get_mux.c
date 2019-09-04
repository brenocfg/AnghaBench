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
typedef  int /*<<< orphan*/  u8 ;
struct rmnet_priv {int /*<<< orphan*/  mux_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rmnet_priv* netdev_priv (struct net_device*) ; 

u8 rmnet_vnd_get_mux(struct net_device *rmnet_dev)
{
	struct rmnet_priv *priv;

	priv = netdev_priv(rmnet_dev);
	return priv->mux_id;
}