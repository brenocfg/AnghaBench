#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_sub_if_data {int /*<<< orphan*/  wdev; TYPE_2__* local; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __ieee80211_csa_finalize (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  cfg80211_stop_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*) ; 

__attribute__((used)) static void ieee80211_csa_finalize(struct ieee80211_sub_if_data *sdata)
{
	if (__ieee80211_csa_finalize(sdata)) {
		sdata_info(sdata, "failed to finalize CSA, disconnecting\n");
		cfg80211_stop_iface(sdata->local->hw.wiphy, &sdata->wdev,
				    GFP_KERNEL);
	}
}