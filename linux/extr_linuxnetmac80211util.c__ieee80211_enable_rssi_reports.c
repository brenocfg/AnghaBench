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
struct TYPE_5__ {int rssi_min_thold; int rssi_max_thold; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  trace_api_enable_rssi_reports (struct ieee80211_sub_if_data*,int,int) ; 

__attribute__((used)) static void _ieee80211_enable_rssi_reports(struct ieee80211_sub_if_data *sdata,
					    int rssi_min_thold,
					    int rssi_max_thold)
{
	trace_api_enable_rssi_reports(sdata, rssi_min_thold, rssi_max_thold);

	if (WARN_ON(sdata->vif.type != NL80211_IFTYPE_STATION))
		return;

	/*
	 * Scale up threshold values before storing it, as the RSSI averaging
	 * algorithm uses a scaled up value as well. Change this scaling
	 * factor if the RSSI averaging algorithm changes.
	 */
	sdata->u.mgd.rssi_min_thold = rssi_min_thold*16;
	sdata->u.mgd.rssi_max_thold = rssi_max_thold*16;
}