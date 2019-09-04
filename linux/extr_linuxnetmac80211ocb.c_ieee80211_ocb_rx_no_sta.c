#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {int /*<<< orphan*/ * supp_rates; } ;
struct sta_info {int /*<<< orphan*/  list; TYPE_5__ sta; } ;
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_if_ocb {int /*<<< orphan*/  incomplete_lock; int /*<<< orphan*/  incomplete_stations; } ;
struct TYPE_8__ {struct ieee80211_if_ocb ocb; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  work; TYPE_2__ vif; int /*<<< orphan*/  name; struct ieee80211_local* local; TYPE_1__ u; } ;
struct TYPE_13__ {TYPE_4__* wiphy; } ;
struct ieee80211_local {scalar_t__ num_sta; TYPE_6__ hw; } ;
struct TYPE_14__ {TYPE_3__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_7__ def; } ;
typedef  enum nl80211_bss_scan_width { ____Placeholder_nl80211_bss_scan_width } nl80211_bss_scan_width ;
struct TYPE_11__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_10__ {int band; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IEEE80211_OCB_MAX_STA_ENTRIES ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int cfg80211_chandef_to_scan_width (TYPE_7__*) ; 
 int /*<<< orphan*/  ieee80211_mandatory_rates (struct ieee80211_supported_band*,int) ; 
 int /*<<< orphan*/  ieee80211_queue_work (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ocb_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/  const*) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_alloc (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void ieee80211_ocb_rx_no_sta(struct ieee80211_sub_if_data *sdata,
			     const u8 *bssid, const u8 *addr,
			     u32 supp_rates)
{
	struct ieee80211_if_ocb *ifocb = &sdata->u.ocb;
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_supported_band *sband;
	enum nl80211_bss_scan_width scan_width;
	struct sta_info *sta;
	int band;

	/* XXX: Consider removing the least recently used entry and
	 *      allow new one to be added.
	 */
	if (local->num_sta >= IEEE80211_OCB_MAX_STA_ENTRIES) {
		net_info_ratelimited("%s: No room for a new OCB STA entry %pM\n",
				     sdata->name, addr);
		return;
	}

	ocb_dbg(sdata, "Adding new OCB station %pM\n", addr);

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (WARN_ON_ONCE(!chanctx_conf)) {
		rcu_read_unlock();
		return;
	}
	band = chanctx_conf->def.chan->band;
	scan_width = cfg80211_chandef_to_scan_width(&chanctx_conf->def);
	rcu_read_unlock();

	sta = sta_info_alloc(sdata, addr, GFP_ATOMIC);
	if (!sta)
		return;

	/* Add only mandatory rates for now */
	sband = local->hw.wiphy->bands[band];
	sta->sta.supp_rates[band] =
		ieee80211_mandatory_rates(sband, scan_width);

	spin_lock(&ifocb->incomplete_lock);
	list_add(&sta->list, &ifocb->incomplete_stations);
	spin_unlock(&ifocb->incomplete_lock);
	ieee80211_queue_work(&local->hw, &sdata->work);
}