#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct minstrel_sta_info {scalar_t__ sample_deferred; scalar_t__ last_stats_update; int /*<<< orphan*/  sample_packets; TYPE_3__* r; } ;
struct minstrel_priv {int update_interval; } ;
struct ieee80211_tx_status {struct ieee80211_tx_info* info; } ;
struct ieee80211_tx_rate {scalar_t__ idx; scalar_t__ count; } ;
struct TYPE_4__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ status; } ;
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_5__ {int success; int /*<<< orphan*/  attempts; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */
 int HZ ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_MAX_RATES ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  minstrel_update_stats (struct minstrel_priv*,struct minstrel_sta_info*) ; 
 int rix_to_ndx (struct minstrel_sta_info*,scalar_t__) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
minstrel_tx_status(void *priv, struct ieee80211_supported_band *sband,
		   void *priv_sta, struct ieee80211_tx_status *st)
{
	struct ieee80211_tx_info *info = st->info;
	struct minstrel_priv *mp = priv;
	struct minstrel_sta_info *mi = priv_sta;
	struct ieee80211_tx_rate *ar = info->status.rates;
	int i, ndx;
	int success;

	success = !!(info->flags & IEEE80211_TX_STAT_ACK);

	for (i = 0; i < IEEE80211_TX_MAX_RATES; i++) {
		if (ar[i].idx < 0)
			break;

		ndx = rix_to_ndx(mi, ar[i].idx);
		if (ndx < 0)
			continue;

		mi->r[ndx].stats.attempts += ar[i].count;

		if ((i != IEEE80211_TX_MAX_RATES - 1) && (ar[i + 1].idx < 0))
			mi->r[ndx].stats.success += success;
	}

	if ((info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) && (i >= 0))
		mi->sample_packets++;

	if (mi->sample_deferred > 0)
		mi->sample_deferred--;

	if (time_after(jiffies, mi->last_stats_update +
				(mp->update_interval * HZ) / 1000))
		minstrel_update_stats(mp, mi);
}