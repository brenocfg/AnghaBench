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
struct ieee80211_tx_info {size_t band; } ;
struct ieee80211_rate {int dummy; } ;
struct ieee80211_hw {TYPE_2__* wiphy; } ;
struct ath5k_buf {TYPE_3__* rates; } ;
struct TYPE_6__ {size_t idx; } ;
struct TYPE_5__ {TYPE_1__** bands; } ;
struct TYPE_4__ {struct ieee80211_rate* bitrates; } ;

/* Variables and functions */

__attribute__((used)) static struct ieee80211_rate *
ath5k_get_rate(const struct ieee80211_hw *hw,
	       const struct ieee80211_tx_info *info,
	       struct ath5k_buf *bf, int idx)
{
	/*
	* convert a ieee80211_tx_rate RC-table entry to
	* the respective ieee80211_rate struct
	*/
	if (bf->rates[idx].idx < 0) {
		return NULL;
	}

	return &hw->wiphy->bands[info->band]->bitrates[ bf->rates[idx].idx ];
}