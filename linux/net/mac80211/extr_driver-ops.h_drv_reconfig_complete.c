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
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
typedef  enum ieee80211_reconfig_type { ____Placeholder_ieee80211_reconfig_type } ieee80211_reconfig_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* reconfig_complete ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_drv_reconfig_complete (struct ieee80211_local*,int) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void
drv_reconfig_complete(struct ieee80211_local *local,
		      enum ieee80211_reconfig_type reconfig_type)
{
	might_sleep();

	trace_drv_reconfig_complete(local, reconfig_type);
	if (local->ops->reconfig_complete)
		local->ops->reconfig_complete(&local->hw, reconfig_type);
	trace_drv_return_void(local);
}