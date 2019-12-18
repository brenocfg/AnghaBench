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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct cfg80211_pmsr_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* abort_pmsr ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_pmsr_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cfg80211_pmsr_request*) ; 
 int /*<<< orphan*/  trace_drv_abort_pmsr (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_abort_pmsr(struct ieee80211_local *local,
				  struct ieee80211_sub_if_data *sdata,
				  struct cfg80211_pmsr_request *request)
{
	trace_drv_abort_pmsr(local, sdata);

	might_sleep();
	if (!check_sdata_in_driver(sdata))
		return;

	if (local->ops->abort_pmsr)
		local->ops->abort_pmsr(&local->hw, &sdata->vif, request);
	trace_drv_return_void(local);
}