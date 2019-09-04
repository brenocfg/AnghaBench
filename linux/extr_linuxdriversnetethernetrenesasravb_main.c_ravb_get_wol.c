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
struct ravb_private {scalar_t__ wol_enabled; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {void* wolopts; void* supported; } ;

/* Variables and functions */
 void* WAKE_MAGIC ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ravb_get_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ravb_private *priv = netdev_priv(ndev);

	wol->supported = WAKE_MAGIC;
	wol->wolopts = priv->wol_enabled ? WAKE_MAGIC : 0;
}