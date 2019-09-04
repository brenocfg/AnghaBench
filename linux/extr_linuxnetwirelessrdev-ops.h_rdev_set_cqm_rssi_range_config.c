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
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int (* set_cqm_rssi_range_config ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_set_cqm_rssi_range_config (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rdev_set_cqm_rssi_range_config(struct cfg80211_registered_device *rdev,
			       struct net_device *dev, s32 low, s32 high)
{
	int ret;
	trace_rdev_set_cqm_rssi_range_config(&rdev->wiphy, dev, low, high);
	ret = rdev->ops->set_cqm_rssi_range_config(&rdev->wiphy, dev,
						   low, high);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}