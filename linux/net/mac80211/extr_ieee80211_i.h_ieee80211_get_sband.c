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
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; struct ieee80211_local* local; } ;
struct TYPE_9__ {TYPE_5__* wiphy; } ;
struct ieee80211_local {TYPE_4__ hw; } ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_3__ def; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_10__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_7__ {int band; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct ieee80211_supported_band *
ieee80211_get_sband(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx_conf *chanctx_conf;
	enum nl80211_band band;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);

	if (WARN_ON_ONCE(!chanctx_conf)) {
		rcu_read_unlock();
		return NULL;
	}

	band = chanctx_conf->def.chan->band;
	rcu_read_unlock();

	return local->hw.wiphy->bands[band];
}