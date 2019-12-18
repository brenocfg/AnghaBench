#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_supported_band {size_t n_bitrates; TYPE_4__* bitrates; } ;
struct TYPE_6__ {int basic_rates; int /*<<< orphan*/  chandef; } ;
struct TYPE_10__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; struct ieee80211_local* local; } ;
struct TYPE_8__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_3__ hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  bitrate; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WLAN_EID_EXT_SUPP_RATES ; 
 int ieee80211_chandef_rate_flags (int /*<<< orphan*/ *) ; 
 int ieee80211_vif_get_shift (TYPE_5__*) ; 
 size_t* skb_put (struct sk_buff*,size_t) ; 
 size_t skb_tailroom (struct sk_buff*) ; 

int ieee80211_add_ext_srates_ie(struct ieee80211_sub_if_data *sdata,
				struct sk_buff *skb, bool need_basic,
				enum nl80211_band band)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_supported_band *sband;
	int rate, shift;
	u8 i, exrates, *pos;
	u32 basic_rates = sdata->vif.bss_conf.basic_rates;
	u32 rate_flags;

	rate_flags = ieee80211_chandef_rate_flags(&sdata->vif.bss_conf.chandef);
	shift = ieee80211_vif_get_shift(&sdata->vif);

	sband = local->hw.wiphy->bands[band];
	exrates = 0;
	for (i = 0; i < sband->n_bitrates; i++) {
		if ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			continue;
		exrates++;
	}

	if (exrates > 8)
		exrates -= 8;
	else
		exrates = 0;

	if (skb_tailroom(skb) < exrates + 2)
		return -ENOMEM;

	if (exrates) {
		pos = skb_put(skb, exrates + 2);
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = exrates;
		for (i = 8; i < sband->n_bitrates; i++) {
			u8 basic = 0;
			if ((rate_flags & sband->bitrates[i].flags)
			    != rate_flags)
				continue;
			if (need_basic && basic_rates & BIT(i))
				basic = 0x80;
			rate = DIV_ROUND_UP(sband->bitrates[i].bitrate,
					    5 * (1 << shift));
			*pos++ = basic | (u8) rate;
		}
	}
	return 0;
}