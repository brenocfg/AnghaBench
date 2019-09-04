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
typedef  int /*<<< orphan*/  u16 ;
struct wireless_dev {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
typedef  enum nl80211_crit_proto_id { ____Placeholder_nl80211_crit_proto_id } nl80211_crit_proto_id ;
struct TYPE_2__ {int (* crit_proto_start ) (int /*<<< orphan*/ *,struct wireless_dev*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wireless_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rdev_crit_proto_start (int /*<<< orphan*/ *,struct wireless_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int rdev_crit_proto_start(struct cfg80211_registered_device *rdev,
					struct wireless_dev *wdev,
					enum nl80211_crit_proto_id protocol,
					u16 duration)
{
	int ret;

	trace_rdev_crit_proto_start(&rdev->wiphy, wdev, protocol, duration);
	ret = rdev->ops->crit_proto_start(&rdev->wiphy, wdev,
					  protocol, duration);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}