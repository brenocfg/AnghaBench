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
struct ocb_setup {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* join_ocb ) (int /*<<< orphan*/ *,struct net_device*,struct ocb_setup*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,struct ocb_setup*) ; 
 int /*<<< orphan*/  trace_rdev_join_ocb (int /*<<< orphan*/ *,struct net_device*,struct ocb_setup*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_join_ocb(struct cfg80211_registered_device *rdev,
				struct net_device *dev,
				struct ocb_setup *setup)
{
	int ret;
	trace_rdev_join_ocb(&rdev->wiphy, dev, setup);
	ret = rdev->ops->join_ocb(&rdev->wiphy, dev, setup);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}