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
struct w5300_priv {int /*<<< orphan*/  link_irq; int /*<<< orphan*/  link_gpio; int /*<<< orphan*/  irq; } ;
struct platform_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  w5300_hw_reset (struct w5300_priv*) ; 

__attribute__((used)) static int w5300_remove(struct platform_device *pdev)
{
	struct net_device *ndev = platform_get_drvdata(pdev);
	struct w5300_priv *priv = netdev_priv(ndev);

	w5300_hw_reset(priv);
	free_irq(priv->irq, ndev);
	if (gpio_is_valid(priv->link_gpio))
		free_irq(priv->link_irq, ndev);

	unregister_netdev(ndev);
	free_netdev(ndev);
	return 0;
}