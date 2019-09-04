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
struct ieee80211_vht_cap {int /*<<< orphan*/  supp_mcs; int /*<<< orphan*/  vht_cap_info; } ;
struct ieee80211_sta_vht_cap {int vht_supported; int /*<<< orphan*/  vht_mcs; int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qtnf_cmd_resp_band_fill_vhtcap(const u8 *info,
					   struct ieee80211_sta_vht_cap *bcap)
{
	const struct ieee80211_vht_cap *vht_cap =
		(const struct ieee80211_vht_cap *)info;

	bcap->vht_supported = true;
	bcap->cap = le32_to_cpu(vht_cap->vht_cap_info);
	memcpy(&bcap->vht_mcs, &vht_cap->supp_mcs, sizeof(bcap->vht_mcs));
}