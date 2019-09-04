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
struct wcn36xx_sta {int /*<<< orphan*/ * vif; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  list; } ;
struct wcn36xx {int /*<<< orphan*/  conf_mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCN36XX_DBG_MAC ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_delete_sta (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (struct ieee80211_sta*) ; 

__attribute__((used)) static int wcn36xx_sta_remove(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_sta *sta)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta remove vif %p sta %pM index %d\n",
		    vif, sta->addr, sta_priv->sta_index);

	mutex_lock(&wcn->conf_mutex);

	list_del(&sta_priv->list);
	wcn36xx_smd_delete_sta(wcn, sta_priv->sta_index);
	sta_priv->vif = NULL;

	mutex_unlock(&wcn->conf_mutex);

	return 0;
}