#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_txq_params {size_t ac; int /*<<< orphan*/  txop; int /*<<< orphan*/  cwmin; int /*<<< orphan*/  cwmax; int /*<<< orphan*/  aifs; } ;
struct ieee80211_tx_queue_params {int uapsd; int /*<<< orphan*/  txop; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  aifs; } ;
struct ieee80211_sub_if_data {struct ieee80211_tx_queue_params* tx_conf; } ;
struct TYPE_4__ {scalar_t__ queues; int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_3__ {int /*<<< orphan*/  conf_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_QOS ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
 scalar_t__ drv_conf_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*,size_t,struct ieee80211_tx_queue_params*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_regulatory_limit_wmm_params (struct ieee80211_sub_if_data*,struct ieee80211_tx_queue_params*,size_t) ; 
 int /*<<< orphan*/  memset (struct ieee80211_tx_queue_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,size_t) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_set_txq_params(struct wiphy *wiphy,
				    struct net_device *dev,
				    struct ieee80211_txq_params *params)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_tx_queue_params p;

	if (!local->ops->conf_tx)
		return -EOPNOTSUPP;

	if (local->hw.queues < IEEE80211_NUM_ACS)
		return -EOPNOTSUPP;

	memset(&p, 0, sizeof(p));
	p.aifs = params->aifs;
	p.cw_max = params->cwmax;
	p.cw_min = params->cwmin;
	p.txop = params->txop;

	/*
	 * Setting tx queue params disables u-apsd because it's only
	 * called in master mode.
	 */
	p.uapsd = false;

	ieee80211_regulatory_limit_wmm_params(sdata, &p, params->ac);

	sdata->tx_conf[params->ac] = p;
	if (drv_conf_tx(local, sdata, params->ac, &p)) {
		wiphy_debug(local->hw.wiphy,
			    "failed to set TX queue parameters for AC %d\n",
			    params->ac);
		return -EINVAL;
	}

	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_QOS);

	return 0;
}