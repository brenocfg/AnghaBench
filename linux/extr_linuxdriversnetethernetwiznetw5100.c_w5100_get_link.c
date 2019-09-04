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
typedef  int u32 ;
struct w5100_priv {int /*<<< orphan*/  link_gpio; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 w5100_get_link(struct net_device *ndev)
{
	struct w5100_priv *priv = netdev_priv(ndev);

	if (gpio_is_valid(priv->link_gpio))
		return !!gpio_get_value(priv->link_gpio);

	return 1;
}