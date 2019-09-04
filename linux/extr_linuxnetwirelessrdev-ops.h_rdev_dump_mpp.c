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
struct mpath_info {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dump_mpp ) (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mpath_info*) ; 
 int /*<<< orphan*/  trace_rdev_dump_mpp (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_return_int_mpath_info (int /*<<< orphan*/ *,int,struct mpath_info*) ; 

__attribute__((used)) static inline int rdev_dump_mpp(struct cfg80211_registered_device *rdev,
				struct net_device *dev, int idx, u8 *dst,
				u8 *mpp, struct mpath_info *pinfo)

{
	int ret;

	trace_rdev_dump_mpp(&rdev->wiphy, dev, idx, dst, mpp);
	ret = rdev->ops->dump_mpp(&rdev->wiphy, dev, idx, dst, mpp, pinfo);
	trace_rdev_return_int_mpath_info(&rdev->wiphy, ret, pinfo);
	return ret;
}