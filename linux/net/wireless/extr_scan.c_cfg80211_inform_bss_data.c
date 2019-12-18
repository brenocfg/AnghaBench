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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct cfg80211_non_tx_bss {struct cfg80211_bss* tx_bss; } ;
struct cfg80211_inform_bss {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum cfg80211_bss_frame_type { ____Placeholder_cfg80211_bss_frame_type } cfg80211_bss_frame_type ;

/* Variables and functions */
 struct cfg80211_bss* cfg80211_inform_single_bss_data (struct wiphy*,struct cfg80211_inform_bss*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_parse_mbssid_data (struct wiphy*,struct cfg80211_inform_bss*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,struct cfg80211_non_tx_bss*,int /*<<< orphan*/ ) ; 

struct cfg80211_bss *
cfg80211_inform_bss_data(struct wiphy *wiphy,
			 struct cfg80211_inform_bss *data,
			 enum cfg80211_bss_frame_type ftype,
			 const u8 *bssid, u64 tsf, u16 capability,
			 u16 beacon_interval, const u8 *ie, size_t ielen,
			 gfp_t gfp)
{
	struct cfg80211_bss *res;
	struct cfg80211_non_tx_bss non_tx_data;

	res = cfg80211_inform_single_bss_data(wiphy, data, ftype, bssid, tsf,
					      capability, beacon_interval, ie,
					      ielen, NULL, gfp);
	if (!res)
		return NULL;
	non_tx_data.tx_bss = res;
	cfg80211_parse_mbssid_data(wiphy, data, ftype, bssid, tsf,
				   beacon_interval, ie, ielen, &non_tx_data,
				   gfp);
	return res;
}