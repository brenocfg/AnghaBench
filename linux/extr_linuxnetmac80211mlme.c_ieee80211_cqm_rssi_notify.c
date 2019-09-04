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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_cqm_rssi_threshold_event { ____Placeholder_nl80211_cqm_rssi_threshold_event } nl80211_cqm_rssi_threshold_event ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_cqm_rssi_notify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_api_cqm_rssi_notify (struct ieee80211_sub_if_data*,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_cqm_rssi_notify(struct ieee80211_vif *vif,
			       enum nl80211_cqm_rssi_threshold_event rssi_event,
			       s32 rssi_level,
			       gfp_t gfp)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);

	trace_api_cqm_rssi_notify(sdata, rssi_event, rssi_level);

	cfg80211_cqm_rssi_notify(sdata->dev, rssi_event, rssi_level, gfp);
}