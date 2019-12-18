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
typedef  int /*<<< orphan*/  u32 ;
struct sta_info {int /*<<< orphan*/  sta; scalar_t__ uploaded; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_expected_throughput ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_get_expected_throughput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_return_u32 (struct ieee80211_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 drv_get_expected_throughput(struct ieee80211_local *local,
					      struct sta_info *sta)
{
	u32 ret = 0;

	trace_drv_get_expected_throughput(&sta->sta);
	if (local->ops->get_expected_throughput && sta->uploaded)
		ret = local->ops->get_expected_throughput(&local->hw, &sta->sta);
	trace_drv_return_u32(local, ret);

	return ret;
}