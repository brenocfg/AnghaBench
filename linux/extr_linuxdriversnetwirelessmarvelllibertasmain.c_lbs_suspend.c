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
struct lbs_private {int deep_sleep_required; scalar_t__ mesh_dev; scalar_t__ dev; scalar_t__ is_deep_sleep; } ;

/* Variables and functions */
 int lbs_set_deep_sleep (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int lbs_set_host_sleep (struct lbs_private*,int) ; 
 int /*<<< orphan*/  netdev_err (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  netif_device_detach (scalar_t__) ; 

int lbs_suspend(struct lbs_private *priv)
{
	int ret;

	if (priv->is_deep_sleep) {
		ret = lbs_set_deep_sleep(priv, 0);
		if (ret) {
			netdev_err(priv->dev,
				   "deep sleep cancellation failed: %d\n", ret);
			return ret;
		}
		priv->deep_sleep_required = 1;
	}

	ret = lbs_set_host_sleep(priv, 1);

	netif_device_detach(priv->dev);
	if (priv->mesh_dev)
		netif_device_detach(priv->mesh_dev);

	return ret;
}