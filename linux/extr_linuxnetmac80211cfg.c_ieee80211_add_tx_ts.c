#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct ieee80211_if_managed {TYPE_3__* tx_tspec; } ;
struct TYPE_4__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int wmm_acm; TYPE_2__ vif; TYPE_1__ u; } ;
struct TYPE_6__ {int admitted_time; size_t tsid; size_t up; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int* ieee802_1d_to_ac ; 

__attribute__((used)) static int ieee80211_add_tx_ts(struct wiphy *wiphy, struct net_device *dev,
			       u8 tsid, const u8 *peer, u8 up,
			       u16 admitted_time)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	int ac = ieee802_1d_to_ac[up];

	if (sdata->vif.type != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	if (!(sdata->wmm_acm & BIT(up)))
		return -EINVAL;

	if (ifmgd->tx_tspec[ac].admitted_time)
		return -EBUSY;

	if (admitted_time) {
		ifmgd->tx_tspec[ac].admitted_time = 32 * admitted_time;
		ifmgd->tx_tspec[ac].tsid = tsid;
		ifmgd->tx_tspec[ac].up = up;
	}

	return 0;
}