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
struct ieee80211_sta_ht_cap {int ht_supported; int ampdu_factor; int ampdu_density; int /*<<< orphan*/  mcs; int /*<<< orphan*/  cap; } ;
struct ieee80211_ht_cap {int ampdu_params_info; int /*<<< orphan*/  mcs; int /*<<< orphan*/  cap_info; } ;

/* Variables and functions */
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qtnf_cmd_resp_band_fill_htcap(const u8 *info,
					  struct ieee80211_sta_ht_cap *bcap)
{
	const struct ieee80211_ht_cap *ht_cap =
		(const struct ieee80211_ht_cap *)info;

	bcap->ht_supported = true;
	bcap->cap = le16_to_cpu(ht_cap->cap_info);
	bcap->ampdu_factor =
		ht_cap->ampdu_params_info & IEEE80211_HT_AMPDU_PARM_FACTOR;
	bcap->ampdu_density =
		(ht_cap->ampdu_params_info & IEEE80211_HT_AMPDU_PARM_DENSITY) >>
		IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT;
	memcpy(&bcap->mcs, &ht_cap->mcs, sizeof(bcap->mcs));
}