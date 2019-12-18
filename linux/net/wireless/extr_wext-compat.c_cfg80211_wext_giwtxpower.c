#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int fixed; int value; int /*<<< orphan*/  disabled; } ;
union iwreq_data {TYPE_2__ txpower; } ;
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  rfkill; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  get_tx_power; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IW_TXPOW_DBM ; 
 int IW_TXPOW_RANGE ; 
 int IW_TXPOW_TYPE ; 
 int rdev_get_tx_power (struct cfg80211_registered_device*,struct wireless_dev*,int*) ; 
 int /*<<< orphan*/  rfkill_blocked (int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wext_giwtxpower(struct net_device *dev,
				    struct iw_request_info *info,
				    union iwreq_data *data, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wdev->wiphy);
	int err, val;

	if ((data->txpower.flags & IW_TXPOW_TYPE) != IW_TXPOW_DBM)
		return -EINVAL;
	if (data->txpower.flags & IW_TXPOW_RANGE)
		return -EINVAL;

	if (!rdev->ops->get_tx_power)
		return -EOPNOTSUPP;

	err = rdev_get_tx_power(rdev, wdev, &val);
	if (err)
		return err;

	/* well... oh well */
	data->txpower.fixed = 1;
	data->txpower.disabled = rfkill_blocked(rdev->rfkill);
	data->txpower.value = val;
	data->txpower.flags = IW_TXPOW_DBM;

	return 0;
}