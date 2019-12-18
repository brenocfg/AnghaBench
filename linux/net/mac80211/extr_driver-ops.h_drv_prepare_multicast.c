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
typedef  int /*<<< orphan*/  u64 ;
struct netdev_hw_addr_list {int /*<<< orphan*/  count; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* prepare_multicast ) (int /*<<< orphan*/ *,struct netdev_hw_addr_list*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct netdev_hw_addr_list*) ; 
 int /*<<< orphan*/  trace_drv_prepare_multicast (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drv_return_u64 (struct ieee80211_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 drv_prepare_multicast(struct ieee80211_local *local,
					struct netdev_hw_addr_list *mc_list)
{
	u64 ret = 0;

	trace_drv_prepare_multicast(local, mc_list->count);

	if (local->ops->prepare_multicast)
		ret = local->ops->prepare_multicast(&local->hw, mc_list);

	trace_drv_return_u64(local, ret);

	return ret;
}