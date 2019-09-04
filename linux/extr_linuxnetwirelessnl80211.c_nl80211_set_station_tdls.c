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
struct station_parameters {scalar_t__ he_capa_len; void* he_capa; void* vht_capa; void* ht_capa; int /*<<< orphan*/  aid; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_ATTR_HE_CAPABILITY ; 
 size_t NL80211_ATTR_HT_CAPABILITY ; 
 size_t NL80211_ATTR_PEER_AID ; 
 size_t NL80211_ATTR_VHT_CAPABILITY ; 
 scalar_t__ NL80211_HE_MIN_CAPABILITY_LEN ; 
 int nl80211_parse_sta_channel_info (struct genl_info*,struct station_parameters*) ; 
 int nl80211_parse_sta_wme (struct genl_info*,struct station_parameters*) ; 
 void* nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 scalar_t__ nla_len (scalar_t__) ; 

__attribute__((used)) static int nl80211_set_station_tdls(struct genl_info *info,
				    struct station_parameters *params)
{
	int err;
	/* Dummy STA entry gets updated once the peer capabilities are known */
	if (info->attrs[NL80211_ATTR_PEER_AID])
		params->aid = nla_get_u16(info->attrs[NL80211_ATTR_PEER_AID]);
	if (info->attrs[NL80211_ATTR_HT_CAPABILITY])
		params->ht_capa =
			nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]);
	if (info->attrs[NL80211_ATTR_VHT_CAPABILITY])
		params->vht_capa =
			nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]);
	if (info->attrs[NL80211_ATTR_HE_CAPABILITY]) {
		params->he_capa =
			nla_data(info->attrs[NL80211_ATTR_HE_CAPABILITY]);
		params->he_capa_len =
			nla_len(info->attrs[NL80211_ATTR_HE_CAPABILITY]);

		if (params->he_capa_len < NL80211_HE_MIN_CAPABILITY_LEN)
			return -EINVAL;
	}

	err = nl80211_parse_sta_channel_info(info, params);
	if (err)
		return err;

	return nl80211_parse_sta_wme(info, params);
}