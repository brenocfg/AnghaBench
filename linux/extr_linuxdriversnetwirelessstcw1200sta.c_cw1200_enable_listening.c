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
struct wsm_start {void* band; int beacon_interval; int dtim_period; int basic_rate_set; int channel_number; int /*<<< orphan*/  probe_delay; int /*<<< orphan*/  mode; } ;
struct cw1200_common {TYPE_1__* channel; } ;
struct TYPE_2__ {scalar_t__ band; int hw_value; } ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_5GHZ ; 
 void* WSM_PHY_BAND_2_4G ; 
 void* WSM_PHY_BAND_5G ; 
 int /*<<< orphan*/  WSM_START_MODE_P2P_DEV ; 
 int wsm_start (struct cw1200_common*,struct wsm_start*) ; 

int cw1200_enable_listening(struct cw1200_common *priv)
{
	struct wsm_start start = {
		.mode = WSM_START_MODE_P2P_DEV,
		.band = WSM_PHY_BAND_2_4G,
		.beacon_interval = 100,
		.dtim_period = 1,
		.probe_delay = 0,
		.basic_rate_set = 0x0F,
	};

	if (priv->channel) {
		start.band = priv->channel->band == NL80211_BAND_5GHZ ?
			     WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;
		start.channel_number = priv->channel->hw_value;
	} else {
		start.band = WSM_PHY_BAND_2_4G;
		start.channel_number = 1;
	}

	return wsm_start(priv, &start);
}