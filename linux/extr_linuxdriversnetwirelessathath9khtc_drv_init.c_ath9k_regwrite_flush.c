#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hw {int dummy; } ;
struct ath_common {scalar_t__ priv; } ;
struct ath9k_htc_priv {TYPE_1__* wmi; } ;
struct TYPE_2__ {int /*<<< orphan*/  multi_write_mutex; scalar_t__ multi_write_idx; int /*<<< orphan*/  mwrite_cnt; } ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_regwrite_multi (struct ath_common*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_regwrite_flush(void *hw_priv)
{
	struct ath_hw *ah = hw_priv;
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_htc_priv *priv = (struct ath9k_htc_priv *) common->priv;

	atomic_dec(&priv->wmi->mwrite_cnt);

	mutex_lock(&priv->wmi->multi_write_mutex);

	if (priv->wmi->multi_write_idx)
		ath9k_regwrite_multi(common);

	mutex_unlock(&priv->wmi->multi_write_mutex);
}