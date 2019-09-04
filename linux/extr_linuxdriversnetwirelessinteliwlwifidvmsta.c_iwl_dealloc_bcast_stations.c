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
struct iwl_priv {scalar_t__ num_stations; int /*<<< orphan*/  sta_lock; TYPE_1__* stations; } ;
struct TYPE_2__ {int used; int /*<<< orphan*/ * lq; } ;

/* Variables and functions */
 int IWLAGN_STATION_COUNT ; 
 int IWL_STA_BCAST ; 
 int IWL_STA_UCODE_ACTIVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_dealloc_bcast_stations(struct iwl_priv *priv)
{
	int i;

	spin_lock_bh(&priv->sta_lock);
	for (i = 0; i < IWLAGN_STATION_COUNT; i++) {
		if (!(priv->stations[i].used & IWL_STA_BCAST))
			continue;

		priv->stations[i].used &= ~IWL_STA_UCODE_ACTIVE;
		priv->num_stations--;
		if (WARN_ON(priv->num_stations < 0))
			priv->num_stations = 0;
		kfree(priv->stations[i].lq);
		priv->stations[i].lq = NULL;
	}
	spin_unlock_bh(&priv->sta_lock);
}