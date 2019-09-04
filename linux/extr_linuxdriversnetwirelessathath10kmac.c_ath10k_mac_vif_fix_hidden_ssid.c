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
struct cfg80211_chan_def {int dummy; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  bssid; int /*<<< orphan*/  aid; struct ath10k* ar; int /*<<< orphan*/  vif; int /*<<< orphan*/  is_up; int /*<<< orphan*/  is_started; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WMI_SERVICE_BEACON_OFFLOAD ; 
 int ath10k_mac_setup_bcn_tmpl (struct ath10k_vif*) ; 
 int ath10k_mac_setup_prb_tmpl (struct ath10k_vif*) ; 
 int ath10k_mac_vif_chan (int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 
 int ath10k_vdev_restart (struct ath10k_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int ath10k_wmi_vdev_down (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_up (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_vif_fix_hidden_ssid(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	struct cfg80211_chan_def def;
	int ret;

	/* When originally vdev is started during assign_vif_chanctx() some
	 * information is missing, notably SSID. Firmware revisions with beacon
	 * offloading require the SSID to be provided during vdev (re)start to
	 * handle hidden SSID properly.
	 *
	 * Vdev restart must be done after vdev has been both started and
	 * upped. Otherwise some firmware revisions (at least 10.2) fail to
	 * deliver vdev restart response event causing timeouts during vdev
	 * syncing in ath10k.
	 *
	 * Note: The vdev down/up and template reinstallation could be skipped
	 * since only wmi-tlv firmware are known to have beacon offload and
	 * wmi-tlv doesn't seem to misbehave like 10.2 wrt vdev restart
	 * response delivery. It's probably more robust to keep it as is.
	 */
	if (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		return 0;

	if (WARN_ON(!arvif->is_started))
		return -EINVAL;

	if (WARN_ON(!arvif->is_up))
		return -EINVAL;

	if (WARN_ON(ath10k_mac_vif_chan(arvif->vif, &def)))
		return -EINVAL;

	ret = ath10k_wmi_vdev_down(ar, arvif->vdev_id);
	if (ret) {
		ath10k_warn(ar, "failed to bring down ap vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	/* Vdev down reset beacon & presp templates. Reinstall them. Otherwise
	 * firmware will crash upon vdev up.
	 */

	ret = ath10k_mac_setup_bcn_tmpl(arvif);
	if (ret) {
		ath10k_warn(ar, "failed to update beacon template: %d\n", ret);
		return ret;
	}

	ret = ath10k_mac_setup_prb_tmpl(arvif);
	if (ret) {
		ath10k_warn(ar, "failed to update presp template: %d\n", ret);
		return ret;
	}

	ret = ath10k_vdev_restart(arvif, &def);
	if (ret) {
		ath10k_warn(ar, "failed to restart ap vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	ret = ath10k_wmi_vdev_up(arvif->ar, arvif->vdev_id, arvif->aid,
				 arvif->bssid);
	if (ret) {
		ath10k_warn(ar, "failed to bring up ap vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}