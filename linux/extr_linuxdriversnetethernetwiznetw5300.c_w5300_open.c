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
struct w5300_priv {int /*<<< orphan*/  link_gpio; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct w5300_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  w5300_hw_start (struct w5300_priv*) ; 

__attribute__((used)) static int w5300_open(struct net_device *ndev)
{
	struct w5300_priv *priv = netdev_priv(ndev);

	netif_info(priv, ifup, ndev, "enabling\n");
	w5300_hw_start(priv);
	napi_enable(&priv->napi);
	netif_start_queue(ndev);
	if (!gpio_is_valid(priv->link_gpio) ||
	    gpio_get_value(priv->link_gpio) != 0)
		netif_carrier_on(ndev);
	return 0;
}