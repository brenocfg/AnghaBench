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
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_dat_tvlv_container_update (struct batadv_priv*) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 

void batadv_dat_status_update(struct net_device *net_dev)
{
	struct batadv_priv *bat_priv = netdev_priv(net_dev);

	batadv_dat_tvlv_container_update(bat_priv);
}