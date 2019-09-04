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
struct TYPE_2__ {int /*<<< orphan*/  flags; scalar_t__ fixed; scalar_t__ disabled; int /*<<< orphan*/  value; } ;
union iwreq_data {TYPE_1__ txpower; } ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  txpow ;
struct wl3501_card {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_TXPOW_MWATT ; 
 int /*<<< orphan*/  WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL ; 
 struct wl3501_card* netdev_priv (struct net_device*) ; 
 int wl3501_get_mib_value (struct wl3501_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wl3501_get_txpow(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	u16 txpow;
	struct wl3501_card *this = netdev_priv(dev);
	int rc = wl3501_get_mib_value(this,
				      WL3501_MIB_ATTR_CURRENT_TX_PWR_LEVEL,
				      &txpow, sizeof(txpow));
	if (!rc) {
		wrqu->txpower.value = txpow;
		wrqu->txpower.disabled = 0;
		/*
		 * From the MIB values I think this can be configurable,
		 * as it lists several tx power levels -acme
		 */
		wrqu->txpower.fixed = 0;
		wrqu->txpower.flags = IW_TXPOW_MWATT;
	}
	return rc;
}