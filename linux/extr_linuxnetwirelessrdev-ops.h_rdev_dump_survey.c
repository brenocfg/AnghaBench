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
struct survey_info {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dump_survey ) (int /*<<< orphan*/ *,struct net_device*,int,struct survey_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int,struct survey_info*) ; 
 int /*<<< orphan*/  trace_rdev_dump_survey (int /*<<< orphan*/ *,struct net_device*,int) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_return_int_survey_info (int /*<<< orphan*/ *,int,struct survey_info*) ; 

__attribute__((used)) static inline int rdev_dump_survey(struct cfg80211_registered_device *rdev,
				   struct net_device *netdev, int idx,
				   struct survey_info *info)
{
	int ret;
	trace_rdev_dump_survey(&rdev->wiphy, netdev, idx);
	ret = rdev->ops->dump_survey(&rdev->wiphy, netdev, idx, info);
	if (ret < 0)
		trace_rdev_return_int(&rdev->wiphy, ret);
	else
		trace_rdev_return_int_survey_info(&rdev->wiphy, ret, info);
	return ret;
}