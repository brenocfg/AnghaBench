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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct regdb_ptrs {int* alpha2; int n_reg_rules; struct ieee80211_reg_rule* reg_rules; } ;
struct iwl_cfg {scalar_t__ nvm_type; } ;
struct ieee80211_regdomain {int* alpha2; int n_reg_rules; struct ieee80211_reg_rule* reg_rules; } ;
struct TYPE_4__ {scalar_t__ max_bandwidth_khz; void* end_freq_khz; void* start_freq_khz; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_eirp; int /*<<< orphan*/  max_antenna_gain; } ;
struct ieee80211_reg_rule {TYPE_2__ freq_range; scalar_t__ flags; TYPE_1__ power_rule; } ;
struct device {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DBI_TO_MBI (int) ; 
 int /*<<< orphan*/  DBM_TO_MBM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct regdb_ptrs* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GEO_WMM_ETSI_5GHZ_INFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IWL_DEBUG_DEV (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IWL_DEFAULT_MAX_TX_POWER ; 
 int /*<<< orphan*/  IWL_DL_LAR ; 
 scalar_t__ IWL_NVM_EXT ; 
 int IWL_NVM_NUM_CHANNELS ; 
 int IWL_NVM_NUM_CHANNELS_EXT ; 
 void* MHZ_TO_KHZ (int) ; 
 int NL80211_BAND_2GHZ ; 
 int NL80211_BAND_5GHZ ; 
 int NL80211_MAX_SUPP_REG_RULES ; 
 scalar_t__ NL80211_RRF_AUTO_BW ; 
 int NUM_2GHZ_CHANNELS ; 
 int NVM_CHANNEL_VALID ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ __le32_to_cpup (int /*<<< orphan*/ *) ; 
 int ieee80211_channel_to_frequency (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/ * iwl_ext_nvm_channels ; 
 int /*<<< orphan*/ * iwl_nvm_channels ; 
 scalar_t__ iwl_nvm_get_regdom_bw_flags (int /*<<< orphan*/  const*,int,int,struct iwl_cfg const*) ; 
 int /*<<< orphan*/  iwl_nvm_print_channel_flags (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int) ; 
 struct regdb_ptrs* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct regdb_ptrs*) ; 
 struct regdb_ptrs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct regdb_ptrs*,struct regdb_ptrs*,int) ; 
 int /*<<< orphan*/  reg_query_regdb_wmm (int*,int,struct ieee80211_reg_rule*) ; 

struct ieee80211_regdomain *
iwl_parse_nvm_mcc_info(struct device *dev, const struct iwl_cfg *cfg,
		       int num_of_ch, __le32 *channels, u16 fw_mcc,
		       u16 geo_info)
{
	int ch_idx;
	u16 ch_flags;
	u32 reg_rule_flags, prev_reg_rule_flags = 0;
	const u8 *nvm_chan = cfg->nvm_type == IWL_NVM_EXT ?
			     iwl_ext_nvm_channels : iwl_nvm_channels;
	struct ieee80211_regdomain *regd, *copy_rd;
	int size_of_regd, regd_to_copy;
	struct ieee80211_reg_rule *rule;
	struct regdb_ptrs *regdb_ptrs;
	enum nl80211_band band;
	int center_freq, prev_center_freq = 0;
	int valid_rules = 0;
	bool new_rule;
	int max_num_ch = cfg->nvm_type == IWL_NVM_EXT ?
			 IWL_NVM_NUM_CHANNELS_EXT : IWL_NVM_NUM_CHANNELS;

	if (WARN_ON_ONCE(num_of_ch > NL80211_MAX_SUPP_REG_RULES))
		return ERR_PTR(-EINVAL);

	if (WARN_ON(num_of_ch > max_num_ch))
		num_of_ch = max_num_ch;

	IWL_DEBUG_DEV(dev, IWL_DL_LAR, "building regdom for %d channels\n",
		      num_of_ch);

	/* build a regdomain rule for every valid channel */
	size_of_regd =
		sizeof(struct ieee80211_regdomain) +
		num_of_ch * sizeof(struct ieee80211_reg_rule);

	regd = kzalloc(size_of_regd, GFP_KERNEL);
	if (!regd)
		return ERR_PTR(-ENOMEM);

	regdb_ptrs = kcalloc(num_of_ch, sizeof(*regdb_ptrs), GFP_KERNEL);
	if (!regdb_ptrs) {
		copy_rd = ERR_PTR(-ENOMEM);
		goto out;
	}

	/* set alpha2 from FW. */
	regd->alpha2[0] = fw_mcc >> 8;
	regd->alpha2[1] = fw_mcc & 0xff;

	for (ch_idx = 0; ch_idx < num_of_ch; ch_idx++) {
		ch_flags = (u16)__le32_to_cpup(channels + ch_idx);
		band = (ch_idx < NUM_2GHZ_CHANNELS) ?
		       NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
		center_freq = ieee80211_channel_to_frequency(nvm_chan[ch_idx],
							     band);
		new_rule = false;

		if (!(ch_flags & NVM_CHANNEL_VALID)) {
			iwl_nvm_print_channel_flags(dev, IWL_DL_LAR,
						    nvm_chan[ch_idx], ch_flags);
			continue;
		}

		reg_rule_flags = iwl_nvm_get_regdom_bw_flags(nvm_chan, ch_idx,
							     ch_flags, cfg);

		/* we can't continue the same rule */
		if (ch_idx == 0 || prev_reg_rule_flags != reg_rule_flags ||
		    center_freq - prev_center_freq > 20) {
			valid_rules++;
			new_rule = true;
		}

		rule = &regd->reg_rules[valid_rules - 1];

		if (new_rule)
			rule->freq_range.start_freq_khz =
						MHZ_TO_KHZ(center_freq - 10);

		rule->freq_range.end_freq_khz = MHZ_TO_KHZ(center_freq + 10);

		/* this doesn't matter - not used by FW */
		rule->power_rule.max_antenna_gain = DBI_TO_MBI(6);
		rule->power_rule.max_eirp =
			DBM_TO_MBM(IWL_DEFAULT_MAX_TX_POWER);

		rule->flags = reg_rule_flags;

		/* rely on auto-calculation to merge BW of contiguous chans */
		rule->flags |= NL80211_RRF_AUTO_BW;
		rule->freq_range.max_bandwidth_khz = 0;

		prev_center_freq = center_freq;
		prev_reg_rule_flags = reg_rule_flags;

		iwl_nvm_print_channel_flags(dev, IWL_DL_LAR,
					    nvm_chan[ch_idx], ch_flags);

		if (!(geo_info & GEO_WMM_ETSI_5GHZ_INFO) ||
		    band == NL80211_BAND_2GHZ)
			continue;

		reg_query_regdb_wmm(regd->alpha2, center_freq, rule);
	}

	regd->n_reg_rules = valid_rules;

	/*
	 * Narrow down regdom for unused regulatory rules to prevent hole
	 * between reg rules to wmm rules.
	 */
	regd_to_copy = sizeof(struct ieee80211_regdomain) +
		valid_rules * sizeof(struct ieee80211_reg_rule);

	copy_rd = kzalloc(regd_to_copy, GFP_KERNEL);
	if (!copy_rd) {
		copy_rd = ERR_PTR(-ENOMEM);
		goto out;
	}

	memcpy(copy_rd, regd, regd_to_copy);

out:
	kfree(regdb_ptrs);
	kfree(regd);
	return copy_rd;
}