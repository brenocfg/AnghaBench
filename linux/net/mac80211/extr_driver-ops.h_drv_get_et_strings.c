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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_et_strings ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_get_et_strings (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_get_et_strings(struct ieee80211_sub_if_data *sdata,
				      u32 sset, u8 *data)
{
	struct ieee80211_local *local = sdata->local;
	if (local->ops->get_et_strings) {
		trace_drv_get_et_strings(local, sset);
		local->ops->get_et_strings(&local->hw, &sdata->vif, sset, data);
		trace_drv_return_void(local);
	}
}