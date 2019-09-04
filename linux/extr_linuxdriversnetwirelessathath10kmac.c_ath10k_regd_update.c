#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct reg_dmn_pair_mapping {int /*<<< orphan*/  reg_5ghz_ctl; int /*<<< orphan*/  reg_2ghz_ctl; int /*<<< orphan*/  reg_domain; } ;
struct TYPE_4__ {struct reg_dmn_pair_mapping* regpair; } ;
struct TYPE_5__ {TYPE_1__ regulatory; } ;
struct ath10k {TYPE_3__* dfs_detector; TYPE_2__ ath_common; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum wmi_dfs_region { ____Placeholder_wmi_dfs_region } wmi_dfs_region ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;
struct TYPE_6__ {int region; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ATH10K_DFS_CERTIFIED ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int WMI_UNINIT_DFS_DOMAIN ; 
 int ath10k_mac_get_dfs_region (int) ; 
 int ath10k_update_channel_list (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_pdev_set_regdomain (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_regd_update(struct ath10k *ar)
{
	struct reg_dmn_pair_mapping *regpair;
	int ret;
	enum wmi_dfs_region wmi_dfs_reg;
	enum nl80211_dfs_regions nl_dfs_reg;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_update_channel_list(ar);
	if (ret)
		ath10k_warn(ar, "failed to update channel list: %d\n", ret);

	regpair = ar->ath_common.regulatory.regpair;

	if (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector) {
		nl_dfs_reg = ar->dfs_detector->region;
		wmi_dfs_reg = ath10k_mac_get_dfs_region(nl_dfs_reg);
	} else {
		wmi_dfs_reg = WMI_UNINIT_DFS_DOMAIN;
	}

	/* Target allows setting up per-band regdomain but ath_common provides
	 * a combined one only
	 */
	ret = ath10k_wmi_pdev_set_regdomain(ar,
					    regpair->reg_domain,
					    regpair->reg_domain, /* 2ghz */
					    regpair->reg_domain, /* 5ghz */
					    regpair->reg_2ghz_ctl,
					    regpair->reg_5ghz_ctl,
					    wmi_dfs_reg);
	if (ret)
		ath10k_warn(ar, "failed to set pdev regdomain: %d\n", ret);
}