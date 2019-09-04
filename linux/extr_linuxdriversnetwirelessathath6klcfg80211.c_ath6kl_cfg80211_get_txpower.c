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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; } ;
struct ath6kl {int tx_pwr; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTED ; 
 int EINTR ; 
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  ath6kl_cfg80211_ready (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 struct ath6kl_vif* ath6kl_vif_first (struct ath6kl*) ; 
 scalar_t__ ath6kl_wmi_get_tx_pwr_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ath6kl_cfg80211_get_txpower(struct wiphy *wiphy,
				       struct wireless_dev *wdev,
				       int *dbm)
{
	struct ath6kl *ar = (struct ath6kl *)wiphy_priv(wiphy);
	struct ath6kl_vif *vif;

	vif = ath6kl_vif_first(ar);
	if (!vif)
		return -EIO;

	if (!ath6kl_cfg80211_ready(vif))
		return -EIO;

	if (test_bit(CONNECTED, &vif->flags)) {
		ar->tx_pwr = 255;

		if (ath6kl_wmi_get_tx_pwr_cmd(ar->wmi, vif->fw_vif_idx) != 0) {
			ath6kl_err("ath6kl_wmi_get_tx_pwr_cmd failed\n");
			return -EIO;
		}

		wait_event_interruptible_timeout(ar->event_wq, ar->tx_pwr != 255,
						 5 * HZ);

		if (signal_pending(current)) {
			ath6kl_err("target did not respond\n");
			return -EINTR;
		}
	}

	*dbm = ar->tx_pwr;
	return 0;
}