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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath6kl_vif {scalar_t__ last_roc_id; int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  ndev; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 struct ath6kl* ath6kl_priv (int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* ath6kl_vif_from_wdev (struct wireless_dev*) ; 
 int ath6kl_wmi_remain_on_chnl_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ath6kl_remain_on_channel(struct wiphy *wiphy,
				    struct wireless_dev *wdev,
				    struct ieee80211_channel *chan,
				    unsigned int duration,
				    u64 *cookie)
{
	struct ath6kl_vif *vif = ath6kl_vif_from_wdev(wdev);
	struct ath6kl *ar = ath6kl_priv(vif->ndev);
	u32 id;

	/* TODO: if already pending or ongoing remain-on-channel,
	 * return -EBUSY */
	id = ++vif->last_roc_id;
	if (id == 0) {
		/* Do not use 0 as the cookie value */
		id = ++vif->last_roc_id;
	}
	*cookie = id;

	return ath6kl_wmi_remain_on_chnl_cmd(ar->wmi, vif->fw_vif_idx,
					     chan->center_freq, duration);
}