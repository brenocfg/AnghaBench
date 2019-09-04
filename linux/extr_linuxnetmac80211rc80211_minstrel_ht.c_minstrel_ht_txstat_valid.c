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
struct minstrel_priv {scalar_t__* cck_rates; } ;
struct ieee80211_tx_rate {scalar_t__ idx; int flags; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_VHT_MCS ; 

__attribute__((used)) static bool
minstrel_ht_txstat_valid(struct minstrel_priv *mp, struct ieee80211_tx_rate *rate)
{
	if (rate->idx < 0)
		return false;

	if (!rate->count)
		return false;

	if (rate->flags & IEEE80211_TX_RC_MCS ||
	    rate->flags & IEEE80211_TX_RC_VHT_MCS)
		return true;

	return rate->idx == mp->cck_rates[0] ||
	       rate->idx == mp->cck_rates[1] ||
	       rate->idx == mp->cck_rates[2] ||
	       rate->idx == mp->cck_rates[3];
}