#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ieee80211_supported_band {int n_bitrates; } ;
struct TYPE_8__ {TYPE_1__* chan; } ;
struct TYPE_9__ {int basic_rates; TYPE_2__ chandef; } ;
struct TYPE_10__ {TYPE_3__ bss_conf; } ;
struct ieee80211_sub_if_data {int* rc_rateidx_mask; TYPE_4__ vif; struct ieee80211_local* local; } ;
struct TYPE_12__ {TYPE_5__* wiphy; } ;
struct ieee80211_local {TYPE_6__ hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_11__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_7__ {int band; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  sdata_dbg (struct ieee80211_sub_if_data*,char*,int,int,int) ; 

void ieee80211_check_rate_mask(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_supported_band *sband;
	u32 user_mask, basic_rates = sdata->vif.bss_conf.basic_rates;
	enum nl80211_band band;

	if (WARN_ON(!sdata->vif.bss_conf.chandef.chan))
		return;

	if (WARN_ON_ONCE(!basic_rates))
		return;

	band = sdata->vif.bss_conf.chandef.chan->band;
	user_mask = sdata->rc_rateidx_mask[band];
	sband = local->hw.wiphy->bands[band];

	if (user_mask & basic_rates)
		return;

	sdata_dbg(sdata,
		  "no overlap between basic rates (0x%x) and user mask (0x%x on band %d) - clearing the latter",
		  basic_rates, user_mask, band);
	sdata->rc_rateidx_mask[band] = (1 << sband->n_bitrates) - 1;
}