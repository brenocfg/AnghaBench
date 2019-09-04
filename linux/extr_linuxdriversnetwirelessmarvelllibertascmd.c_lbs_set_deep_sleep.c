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
struct lbs_private {int is_deep_sleep; int (* enter_deep_sleep ) (struct lbs_private*) ;int (* exit_deep_sleep ) (struct lbs_private*) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int lbs_wait_for_ds_awake (struct lbs_private*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int stub1 (struct lbs_private*) ; 
 int stub2 (struct lbs_private*) ; 

int lbs_set_deep_sleep(struct lbs_private *priv, int deep_sleep)
{
	int ret =  0;

	if (deep_sleep) {
		if (priv->is_deep_sleep != 1) {
			lbs_deb_cmd("deep sleep: sleep\n");
			BUG_ON(!priv->enter_deep_sleep);
			ret = priv->enter_deep_sleep(priv);
			if (!ret) {
				netif_stop_queue(priv->dev);
				netif_carrier_off(priv->dev);
			}
		} else {
			netdev_err(priv->dev, "deep sleep: already enabled\n");
		}
	} else {
		if (priv->is_deep_sleep) {
			lbs_deb_cmd("deep sleep: wakeup\n");
			BUG_ON(!priv->exit_deep_sleep);
			ret = priv->exit_deep_sleep(priv);
			if (!ret) {
				ret = lbs_wait_for_ds_awake(priv);
				if (ret)
					netdev_err(priv->dev,
						   "deep sleep: wakeup failed\n");
			}
		}
	}

	return ret;
}