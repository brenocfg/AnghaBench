#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int skip_table; TYPE_3__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_4__ control; } ;
struct ieee80211_supported_band {size_t band; int n_bitrates; TYPE_2__* bitrates; } ;
struct ieee80211_sta {int* supp_rates; int /*<<< orphan*/ * addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  chandef; } ;
struct ieee80211_hw {int max_rate_tries; TYPE_1__ conf; } ;
struct TYPE_7__ {int idx; int count; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_RATE_ERP_G ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_NO_CCK_RATE ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ *,int,size_t,int,int) ; 
 int ieee80211_chandef_rate_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rate_supported (struct ieee80211_sta*,size_t,int) ; 

__attribute__((used)) static void __rate_control_send_low(struct ieee80211_hw *hw,
				    struct ieee80211_supported_band *sband,
				    struct ieee80211_sta *sta,
				    struct ieee80211_tx_info *info,
				    u32 rate_mask)
{
	int i;
	u32 rate_flags =
		ieee80211_chandef_rate_flags(&hw->conf.chandef);

	if ((sband->band == NL80211_BAND_2GHZ) &&
	    (info->flags & IEEE80211_TX_CTL_NO_CCK_RATE))
		rate_flags |= IEEE80211_RATE_ERP_G;

	info->control.rates[0].idx = 0;
	for (i = 0; i < sband->n_bitrates; i++) {
		if (!(rate_mask & BIT(i)))
			continue;

		if ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			continue;

		if (!rate_supported(sta, sband->band, i))
			continue;

		info->control.rates[0].idx = i;
		break;
	}
	WARN_ONCE(i == sband->n_bitrates,
		  "no supported rates for sta %pM (0x%x, band %d) in rate_mask 0x%x with flags 0x%x\n",
		  sta ? sta->addr : NULL,
		  sta ? sta->supp_rates[sband->band] : -1,
		  sband->band,
		  rate_mask, rate_flags);

	info->control.rates[0].count =
		(info->flags & IEEE80211_TX_CTL_NO_ACK) ?
		1 : hw->max_rate_tries;

	info->control.skip_table = 1;
}