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
struct w5100_priv {int /*<<< orphan*/  xfer_wq; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  setrx_work; int /*<<< orphan*/  link_irq; int /*<<< orphan*/  link_gpio; int /*<<< orphan*/  irq; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  w5100_hw_reset (struct w5100_priv*) ; 

int w5100_remove(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct w5100_priv *priv = netdev_priv(ndev);

	w5100_hw_reset(priv);
	free_irq(priv->irq, ndev);
	if (gpio_is_valid(priv->link_gpio))
		free_irq(priv->link_irq, ndev);

	flush_work(&priv->setrx_work);
	flush_work(&priv->restart_work);
	destroy_workqueue(priv->xfer_wq);

	unregister_netdev(ndev);
	free_netdev(ndev);
	return 0;
}