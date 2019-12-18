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
typedef  enum nl80211_tx_power_setting { ____Placeholder_nl80211_tx_power_setting } nl80211_tx_power_setting ;
struct TYPE_2__ {int (* set_tx_power ) (int /*<<< orphan*/ *,struct wireless_dev*,int,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wireless_dev*,int,int) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_set_tx_power (int /*<<< orphan*/ *,struct wireless_dev*,int,int) ; 

__attribute__((used)) static inline int rdev_set_tx_power(struct cfg80211_registered_device *rdev,
				    struct wireless_dev *wdev,
				    enum nl80211_tx_power_setting type, int mbm)
{
	int ret;
	trace_rdev_set_tx_power(&rdev->wiphy, wdev, type, mbm);
	ret = rdev->ops->set_tx_power(&rdev->wiphy, wdev, type, mbm);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}