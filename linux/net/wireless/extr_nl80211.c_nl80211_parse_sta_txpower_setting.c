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
struct TYPE_4__ {int /*<<< orphan*/  power; int /*<<< orphan*/  type; } ;
struct station_parameters {int /*<<< orphan*/  sta_modify_mask; TYPE_2__ txpwr; } ;
struct genl_info {scalar_t__* attrs; struct cfg80211_registered_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_tx_power; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NL80211_ATTR_STA_TX_POWER ; 
 size_t NL80211_ATTR_STA_TX_POWER_SETTING ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_STA_TX_PWR ; 
 int /*<<< orphan*/  NL80211_TX_POWER_LIMITED ; 
 int /*<<< orphan*/  STATION_PARAM_APPLY_STA_TXPOWER ; 
 int /*<<< orphan*/  nla_get_s16 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_parse_sta_txpower_setting(struct genl_info *info,
					     struct station_parameters *params)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	int idx;

	if (info->attrs[NL80211_ATTR_STA_TX_POWER_SETTING]) {
		if (!rdev->ops->set_tx_power ||
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					 NL80211_EXT_FEATURE_STA_TX_PWR))
			return -EOPNOTSUPP;

		idx = NL80211_ATTR_STA_TX_POWER_SETTING;
		params->txpwr.type = nla_get_u8(info->attrs[idx]);

		if (params->txpwr.type == NL80211_TX_POWER_LIMITED) {
			idx = NL80211_ATTR_STA_TX_POWER;

			if (info->attrs[idx])
				params->txpwr.power =
					nla_get_s16(info->attrs[idx]);
			else
				return -EINVAL;
		}
		params->sta_modify_mask |= STATION_PARAM_APPLY_STA_TXPOWER;
	}

	return 0;
}