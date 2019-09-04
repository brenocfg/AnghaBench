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
struct ks_wlan_private {int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int ks_wlan_hw_power_save(struct ks_wlan_private *priv)
{
	queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
	return 0;
}