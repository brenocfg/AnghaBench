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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; struct nlattr** attrs; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_ATTR_CQM ; 
 int /*<<< orphan*/  NL80211_ATTR_CQM_MAX ; 
 size_t NL80211_ATTR_CQM_RSSI_HYST ; 
 size_t NL80211_ATTR_CQM_RSSI_THOLD ; 
 size_t NL80211_ATTR_CQM_TXE_INTVL ; 
 size_t NL80211_ATTR_CQM_TXE_PKTS ; 
 size_t NL80211_ATTR_CQM_TXE_RATE ; 
 int /*<<< orphan*/  nl80211_attr_cqm_policy ; 
 int nl80211_set_cqm_rssi (struct genl_info*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int nl80211_set_cqm_txe (struct genl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_set_cqm(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attrs[NL80211_ATTR_CQM_MAX + 1];
	struct nlattr *cqm;
	int err;

	cqm = info->attrs[NL80211_ATTR_CQM];
	if (!cqm)
		return -EINVAL;

	err = nla_parse_nested_deprecated(attrs, NL80211_ATTR_CQM_MAX, cqm,
					  nl80211_attr_cqm_policy,
					  info->extack);
	if (err)
		return err;

	if (attrs[NL80211_ATTR_CQM_RSSI_THOLD] &&
	    attrs[NL80211_ATTR_CQM_RSSI_HYST]) {
		const s32 *thresholds =
			nla_data(attrs[NL80211_ATTR_CQM_RSSI_THOLD]);
		int len = nla_len(attrs[NL80211_ATTR_CQM_RSSI_THOLD]);
		u32 hysteresis = nla_get_u32(attrs[NL80211_ATTR_CQM_RSSI_HYST]);

		if (len % 4)
			return -EINVAL;

		return nl80211_set_cqm_rssi(info, thresholds, len / 4,
					    hysteresis);
	}

	if (attrs[NL80211_ATTR_CQM_TXE_RATE] &&
	    attrs[NL80211_ATTR_CQM_TXE_PKTS] &&
	    attrs[NL80211_ATTR_CQM_TXE_INTVL]) {
		u32 rate = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_RATE]);
		u32 pkts = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_PKTS]);
		u32 intvl = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_INTVL]);

		return nl80211_set_cqm_txe(info, rate, pkts, intvl);
	}

	return -EINVAL;
}