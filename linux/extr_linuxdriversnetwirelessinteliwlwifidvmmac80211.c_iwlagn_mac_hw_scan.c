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
struct iwl_priv {scalar_t__ scan_type; int /*<<< orphan*/  mutex; struct ieee80211_vif* scan_vif; struct cfg80211_scan_request* scan_request; } ;
struct ieee80211_vif {int dummy; } ;
struct cfg80211_scan_request {scalar_t__ n_channels; TYPE_1__** channels; } ;
struct ieee80211_scan_request {struct cfg80211_scan_request req; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 struct iwl_priv* IWL_MAC80211_GET_DVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_SCAN_NORMAL ; 
 int iwl_scan_initiate (struct iwl_priv*,struct ieee80211_vif*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_mac_hw_scan(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      struct ieee80211_scan_request *hw_req)
{
	struct iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	struct cfg80211_scan_request *req = &hw_req->req;
	int ret;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	if (req->n_channels == 0)
		return -EINVAL;

	mutex_lock(&priv->mutex);

	/*
	 * If an internal scan is in progress, just set
	 * up the scan_request as per above.
	 */
	if (priv->scan_type != IWL_SCAN_NORMAL) {
		IWL_DEBUG_SCAN(priv,
			       "SCAN request during internal scan - defer\n");
		priv->scan_request = req;
		priv->scan_vif = vif;
		ret = 0;
	} else {
		priv->scan_request = req;
		priv->scan_vif = vif;
		/*
		 * mac80211 will only ask for one band at a time
		 * so using channels[0] here is ok
		 */
		ret = iwl_scan_initiate(priv, vif, IWL_SCAN_NORMAL,
					req->channels[0]->band);
		if (ret) {
			priv->scan_request = NULL;
			priv->scan_vif = NULL;
		}
	}

	IWL_DEBUG_MAC80211(priv, "leave\n");

	mutex_unlock(&priv->mutex);

	return ret;
}