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
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {TYPE_1__* wiphy; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int disabled; int fixed; int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  rts_threshold; } ;

/* Variables and functions */

int cfg80211_wext_giwrts(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_param *rts, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	rts->value = wdev->wiphy->rts_threshold;
	rts->disabled = rts->value == (u32) -1;
	rts->fixed = 1;

	return 0;
}