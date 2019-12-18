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
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* add_mpath ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_add_mpath (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_add_mpath(struct cfg80211_registered_device *rdev,
				 struct net_device *dev, u8 *dst, u8 *next_hop)
{
	int ret;
	trace_rdev_add_mpath(&rdev->wiphy, dev, dst, next_hop);
	ret = rdev->ops->add_mpath(&rdev->wiphy, dev, dst, next_hop);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}