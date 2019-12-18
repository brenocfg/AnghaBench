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
typedef  int u8 ;
typedef  int u16 ;
struct minstrel_rate_stats {scalar_t__ prob_ewma; int retry_count; int retry_count_rtscts; int /*<<< orphan*/  retry_updated; } ;
struct minstrel_priv {int* cck_rates; } ;
struct minstrel_ht_sta {TYPE_1__* sta; } ;
struct mcs_group {int flags; int streams; } ;
struct ieee80211_sta_rates {TYPE_2__* rate; } ;
struct TYPE_4__ {int count; int count_rts; int count_cts; int idx; int flags; } ;
struct TYPE_3__ {scalar_t__ smps_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_TX_RC_USE_RTS_CTS ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int MCS_GROUP_RATES ; 
 int MINSTREL_CCK_GROUP ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 int /*<<< orphan*/  minstrel_calc_retransmit (struct minstrel_priv*,struct minstrel_ht_sta*,int) ; 
 struct minstrel_rate_stats* minstrel_get_ratestats (struct minstrel_ht_sta*,int) ; 
 struct mcs_group* minstrel_mcs_groups ; 

__attribute__((used)) static void
minstrel_ht_set_rate(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
                     struct ieee80211_sta_rates *ratetbl, int offset, int index)
{
	const struct mcs_group *group = &minstrel_mcs_groups[index / MCS_GROUP_RATES];
	struct minstrel_rate_stats *mrs;
	u8 idx;
	u16 flags = group->flags;

	mrs = minstrel_get_ratestats(mi, index);
	if (!mrs->retry_updated)
		minstrel_calc_retransmit(mp, mi, index);

	if (mrs->prob_ewma < MINSTREL_FRAC(20, 100) || !mrs->retry_count) {
		ratetbl->rate[offset].count = 2;
		ratetbl->rate[offset].count_rts = 2;
		ratetbl->rate[offset].count_cts = 2;
	} else {
		ratetbl->rate[offset].count = mrs->retry_count;
		ratetbl->rate[offset].count_cts = mrs->retry_count;
		ratetbl->rate[offset].count_rts = mrs->retry_count_rtscts;
	}

	if (index / MCS_GROUP_RATES == MINSTREL_CCK_GROUP)
		idx = mp->cck_rates[index % ARRAY_SIZE(mp->cck_rates)];
	else if (flags & IEEE80211_TX_RC_VHT_MCS)
		idx = ((group->streams - 1) << 4) |
		      ((index % MCS_GROUP_RATES) & 0xF);
	else
		idx = index % MCS_GROUP_RATES + (group->streams - 1) * 8;

	/* enable RTS/CTS if needed:
	 *  - if station is in dynamic SMPS (and streams > 1)
	 *  - for fallback rates, to increase chances of getting through
	 */
	if (offset > 0 ||
	    (mi->sta->smps_mode == IEEE80211_SMPS_DYNAMIC &&
	     group->streams > 1)) {
		ratetbl->rate[offset].count = ratetbl->rate[offset].count_rts;
		flags |= IEEE80211_TX_RC_USE_RTS_CTS;
	}

	ratetbl->rate[offset].idx = idx;
	ratetbl->rate[offset].flags = flags;
}