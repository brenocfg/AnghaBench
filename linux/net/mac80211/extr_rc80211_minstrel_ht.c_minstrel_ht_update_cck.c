#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct minstrel_priv {int /*<<< orphan*/ * cck_rates; int /*<<< orphan*/  hw; } ;
struct minstrel_ht_sta {int /*<<< orphan*/  cck_supported; int /*<<< orphan*/ * supported; int /*<<< orphan*/  cck_supported_short; } ;
struct ieee80211_supported_band {scalar_t__ band; TYPE_1__* bitrates; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int IEEE80211_RATE_SHORT_PREAMBLE ; 
 size_t MINSTREL_CCK_GROUP ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  SUPPORTS_HT_CCK_RATES ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_supported (struct ieee80211_sta*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
minstrel_ht_update_cck(struct minstrel_priv *mp, struct minstrel_ht_sta *mi,
		       struct ieee80211_supported_band *sband,
		       struct ieee80211_sta *sta)
{
	int i;

	if (sband->band != NL80211_BAND_2GHZ)
		return;

	if (!ieee80211_hw_check(mp->hw, SUPPORTS_HT_CCK_RATES))
		return;

	mi->cck_supported = 0;
	mi->cck_supported_short = 0;
	for (i = 0; i < 4; i++) {
		if (!rate_supported(sta, sband->band, mp->cck_rates[i]))
			continue;

		mi->cck_supported |= BIT(i);
		if (sband->bitrates[i].flags & IEEE80211_RATE_SHORT_PREAMBLE)
			mi->cck_supported_short |= BIT(i);
	}

	mi->supported[MINSTREL_CCK_GROUP] = mi->cck_supported;
}