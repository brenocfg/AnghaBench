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
struct mwifiex_private {int dummy; } ;
struct cfg80211_beacon_data {int dummy; } ;

/* Variables and functions */
 int mwifiex_set_mgmt_beacon_data_ies (struct mwifiex_private*,struct cfg80211_beacon_data*) ; 
 int mwifiex_uap_parse_tail_ies (struct mwifiex_private*,struct cfg80211_beacon_data*) ; 

int mwifiex_set_mgmt_ies(struct mwifiex_private *priv,
			 struct cfg80211_beacon_data *info)
{
	int ret;

	ret = mwifiex_uap_parse_tail_ies(priv, info);

	if (ret)
		return ret;

	return mwifiex_set_mgmt_beacon_data_ies(priv, info);
}