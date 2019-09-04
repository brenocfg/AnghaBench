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
struct lbs_private {int /*<<< orphan*/  dev; scalar_t__ is_deep_sleep; int /*<<< orphan*/  ds_awake_q; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lbs_wait_for_ds_awake(struct lbs_private *priv)
{
	int ret = 0;

	if (priv->is_deep_sleep) {
		if (!wait_event_interruptible_timeout(priv->ds_awake_q,
					!priv->is_deep_sleep, (10 * HZ))) {
			netdev_err(priv->dev, "ds_awake_q: timer expired\n");
			ret = -1;
		}
	}

	return ret;
}