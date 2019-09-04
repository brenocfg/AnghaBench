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
struct ieee80211_hw {TYPE_1__* wiphy; struct cw1200_common* priv; } ;
struct cw1200_common {int setbssparams_done; int wep_default_key_id; int cqm_beacon_loss_count; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  mode; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  edca; int /*<<< orphan*/  pm_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  WSM_EDCA_SET (int /*<<< orphan*/ *,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cw1200_pm_stay_awake (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cw1200_set_uapsd_param (struct cw1200_common*,int /*<<< orphan*/ *) ; 
 int cw1200_setup_mac (struct cw1200_common*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wsm_set_edca_params (struct cw1200_common*,int /*<<< orphan*/ *) ; 

int cw1200_start(struct ieee80211_hw *dev)
{
	struct cw1200_common *priv = dev->priv;
	int ret = 0;

	cw1200_pm_stay_awake(&priv->pm_state, HZ);

	mutex_lock(&priv->conf_mutex);

	/* default EDCA */
	WSM_EDCA_SET(&priv->edca, 0, 0x0002, 0x0003, 0x0007, 47, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 1, 0x0002, 0x0007, 0x000f, 94, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 2, 0x0003, 0x000f, 0x03ff, 0, 0xc8, false);
	WSM_EDCA_SET(&priv->edca, 3, 0x0007, 0x000f, 0x03ff, 0, 0xc8, false);
	ret = wsm_set_edca_params(priv, &priv->edca);
	if (ret)
		goto out;

	ret = cw1200_set_uapsd_param(priv, &priv->edca);
	if (ret)
		goto out;

	priv->setbssparams_done = false;

	memcpy(priv->mac_addr, dev->wiphy->perm_addr, ETH_ALEN);
	priv->mode = NL80211_IFTYPE_MONITOR;
	priv->wep_default_key_id = -1;

	priv->cqm_beacon_loss_count = 10;

	ret = cw1200_setup_mac(priv);
	if (ret)
		goto out;

out:
	mutex_unlock(&priv->conf_mutex);
	return ret;
}