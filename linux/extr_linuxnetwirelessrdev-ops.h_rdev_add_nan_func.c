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
struct wireless_dev {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct cfg80211_nan_func {int dummy; } ;
struct TYPE_2__ {int (* add_nan_func ) (int /*<<< orphan*/ *,struct wireless_dev*,struct cfg80211_nan_func*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wireless_dev*,struct cfg80211_nan_func*) ; 
 int /*<<< orphan*/  trace_rdev_add_nan_func (int /*<<< orphan*/ *,struct wireless_dev*,struct cfg80211_nan_func*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
rdev_add_nan_func(struct cfg80211_registered_device *rdev,
		  struct wireless_dev *wdev,
		  struct cfg80211_nan_func *nan_func)
{
	int ret;

	trace_rdev_add_nan_func(&rdev->wiphy, wdev, nan_func);
	ret = rdev->ops->add_nan_func(&rdev->wiphy, wdev, nan_func);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}