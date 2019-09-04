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
typedef  int u32 ;
typedef  int u16 ;
struct wiphy {int n_iface_combinations; struct ieee80211_iface_combination* iface_combinations; } ;
struct wil_fw_record_concurrency {int n_mids; struct wil_fw_concurrency_combo* combos; int /*<<< orphan*/  n_combos; } ;
struct wil_fw_concurrency_limit {int /*<<< orphan*/  types; int /*<<< orphan*/  max; } ;
struct wil_fw_concurrency_combo {int n_limits; struct wil_fw_concurrency_limit* limits; int /*<<< orphan*/  same_bi; int /*<<< orphan*/  n_diff_channels; int /*<<< orphan*/  max_interfaces; } ;
struct wil6210_priv {int max_vifs; } ;
struct ieee80211_iface_limit {void* types; void* max; } ;
struct ieee80211_iface_combination {int n_limits; struct ieee80211_iface_limit* limits; int /*<<< orphan*/  beacon_int_infra_match; int /*<<< orphan*/  num_different_channels; int /*<<< orphan*/  max_interfaces; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WIL_MAX_VIFS ; 
 struct ieee80211_iface_combination* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_info (struct wil6210_priv*,char*,int,int) ; 
 struct wiphy* wil_to_wiphy (struct wil6210_priv*) ; 

int wil_cfg80211_iface_combinations_from_fw(
	struct wil6210_priv *wil, const struct wil_fw_record_concurrency *conc)
{
	struct wiphy *wiphy = wil_to_wiphy(wil);
	u32 total_limits = 0;
	u16 n_combos;
	const struct wil_fw_concurrency_combo *combo;
	const struct wil_fw_concurrency_limit *limit;
	struct ieee80211_iface_combination *iface_combinations;
	struct ieee80211_iface_limit *iface_limit;
	int i, j;

	if (wiphy->iface_combinations) {
		wil_dbg_misc(wil, "iface_combinations already set, skipping\n");
		return 0;
	}

	combo = conc->combos;
	n_combos = le16_to_cpu(conc->n_combos);
	for (i = 0; i < n_combos; i++) {
		total_limits += combo->n_limits;
		limit = combo->limits + combo->n_limits;
		combo = (struct wil_fw_concurrency_combo *)limit;
	}

	iface_combinations =
		kzalloc(n_combos * sizeof(struct ieee80211_iface_combination) +
			total_limits * sizeof(struct ieee80211_iface_limit),
			GFP_KERNEL);
	if (!iface_combinations)
		return -ENOMEM;
	iface_limit = (struct ieee80211_iface_limit *)(iface_combinations +
						       n_combos);
	combo = conc->combos;
	for (i = 0; i < n_combos; i++) {
		iface_combinations[i].max_interfaces = combo->max_interfaces;
		iface_combinations[i].num_different_channels =
			combo->n_diff_channels;
		iface_combinations[i].beacon_int_infra_match =
			combo->same_bi;
		iface_combinations[i].n_limits = combo->n_limits;
		wil_dbg_misc(wil,
			     "iface_combination %d: max_if %d, num_ch %d, bi_match %d\n",
			     i, iface_combinations[i].max_interfaces,
			     iface_combinations[i].num_different_channels,
			     iface_combinations[i].beacon_int_infra_match);
		limit = combo->limits;
		for (j = 0; j < combo->n_limits; j++) {
			iface_limit[j].max = le16_to_cpu(limit[j].max);
			iface_limit[j].types = le16_to_cpu(limit[j].types);
			wil_dbg_misc(wil,
				     "limit %d: max %d types 0x%x\n", j,
				     iface_limit[j].max, iface_limit[j].types);
		}
		iface_combinations[i].limits = iface_limit;
		iface_limit += combo->n_limits;
		limit += combo->n_limits;
		combo = (struct wil_fw_concurrency_combo *)limit;
	}

	wil_dbg_misc(wil, "multiple VIFs supported, n_mids %d\n", conc->n_mids);
	wil->max_vifs = conc->n_mids + 1; /* including main interface */
	if (wil->max_vifs > WIL_MAX_VIFS) {
		wil_info(wil, "limited number of VIFs supported(%d, FW %d)\n",
			 WIL_MAX_VIFS, wil->max_vifs);
		wil->max_vifs = WIL_MAX_VIFS;
	}
	wiphy->n_iface_combinations = n_combos;
	wiphy->iface_combinations = iface_combinations;
	return 0;
}