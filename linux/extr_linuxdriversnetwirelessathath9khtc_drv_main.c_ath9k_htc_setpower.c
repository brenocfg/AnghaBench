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
struct ath9k_htc_priv {int /*<<< orphan*/  htc_pm_lock; int /*<<< orphan*/  ah; } ;
typedef  enum ath9k_power_mode { ____Placeholder_ath9k_power_mode } ath9k_power_mode ;

/* Variables and functions */
 int ath9k_hw_setpower (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool ath9k_htc_setpower(struct ath9k_htc_priv *priv,
			enum ath9k_power_mode mode)
{
	bool ret;

	mutex_lock(&priv->htc_pm_lock);
	ret = ath9k_hw_setpower(priv->ah, mode);
	mutex_unlock(&priv->htc_pm_lock);

	return ret;
}