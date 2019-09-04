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
struct survey_info {scalar_t__ time_tx; scalar_t__ time_busy; scalar_t__ time; } ;
struct TYPE_2__ {scalar_t__ tx; scalar_t__ cca; scalar_t__ active; } ;
struct p54_common {int update_stats; TYPE_1__ survey_raw; struct survey_info* survey; struct ieee80211_channel* curchan; } ;
struct ieee80211_channel {size_t hw_value; } ;

/* Variables and functions */

__attribute__((used)) static void p54_reset_stats(struct p54_common *priv)
{
	struct ieee80211_channel *chan = priv->curchan;

	if (chan) {
		struct survey_info *info = &priv->survey[chan->hw_value];

		/* only reset channel statistics, don't touch .filled, etc. */
		info->time = 0;
		info->time_busy = 0;
		info->time_tx = 0;
	}

	priv->update_stats = true;
	priv->survey_raw.active = 0;
	priv->survey_raw.cca = 0;
	priv->survey_raw.tx = 0;
}