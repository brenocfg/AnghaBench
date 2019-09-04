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
struct ieee80211_tx_rate {size_t idx; int flags; } ;
struct ieee80211_rate {int dummy; } ;
struct cw1200_common {TYPE_2__* channel; TYPE_1__* hw; struct ieee80211_rate const* mcs_rates; } ;
struct TYPE_8__ {TYPE_3__** bands; } ;
struct TYPE_7__ {struct ieee80211_rate const* bitrates; } ;
struct TYPE_6__ {size_t band; } ;
struct TYPE_5__ {TYPE_4__* wiphy; } ;

/* Variables and functions */
 int IEEE80211_TX_RC_MCS ; 

__attribute__((used)) static const struct ieee80211_rate *
cw1200_get_tx_rate(const struct cw1200_common *priv,
		   const struct ieee80211_tx_rate *rate)
{
	if (rate->idx < 0)
		return NULL;
	if (rate->flags & IEEE80211_TX_RC_MCS)
		return &priv->mcs_rates[rate->idx];
	return &priv->hw->wiphy->bands[priv->channel->band]->
		bitrates[rate->idx];
}