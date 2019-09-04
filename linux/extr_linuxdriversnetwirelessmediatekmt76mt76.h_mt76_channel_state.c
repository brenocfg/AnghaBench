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
struct TYPE_2__ {struct ieee80211_channel* channels; } ;
struct mt76_sband {struct mt76_channel_state* chan; TYPE_1__ sband; } ;
struct mt76_dev {struct mt76_sband sband_5g; struct mt76_sband sband_2g; } ;
struct mt76_channel_state {int dummy; } ;
struct ieee80211_channel {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 

__attribute__((used)) static inline struct mt76_channel_state *
mt76_channel_state(struct mt76_dev *dev, struct ieee80211_channel *c)
{
	struct mt76_sband *msband;
	int idx;

	if (c->band == NL80211_BAND_2GHZ)
		msband = &dev->sband_2g;
	else
		msband = &dev->sband_5g;

	idx = c - &msband->sband.channels[0];
	return &msband->chan[idx];
}