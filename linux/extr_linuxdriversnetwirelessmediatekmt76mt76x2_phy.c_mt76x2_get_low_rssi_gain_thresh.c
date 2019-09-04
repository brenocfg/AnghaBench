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
struct TYPE_3__ {int width; } ;
struct TYPE_4__ {TYPE_1__ chandef; } ;
struct mt76x2_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_40 129 
#define  NL80211_CHAN_WIDTH_80 128 

__attribute__((used)) static int
mt76x2_get_low_rssi_gain_thresh(struct mt76x2_dev *dev)
{
	switch (dev->mt76.chandef.width) {
	case NL80211_CHAN_WIDTH_80:
		return -76;
	case NL80211_CHAN_WIDTH_40:
		return -79;
	default:
		return -82;
	}
}