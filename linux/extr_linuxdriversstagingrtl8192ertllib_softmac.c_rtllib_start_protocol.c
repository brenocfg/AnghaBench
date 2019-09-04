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
struct TYPE_2__ {short channel; int beacon_interval; } ;
struct rtllib_device {int proto_started; int* last_rxseq_num; int* last_rxfrag_num; scalar_t__ iw_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* UpdateBeaconInterruptHandler ) (int /*<<< orphan*/ ,int) ;scalar_t__ wmm_acm; scalar_t__* last_packet_time; TYPE_1__ current_network; int /*<<< orphan*/ * active_channel_map; } ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 scalar_t__ IW_MODE_MONITOR ; 
 short MAX_CHANNEL_NUMBER ; 
 int /*<<< orphan*/  rtllib_start_bss (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_start_ibss (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_start_master_bss (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_start_monitor_mode (struct rtllib_device*) ; 
 int /*<<< orphan*/  rtllib_update_active_chan_map (struct rtllib_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

void rtllib_start_protocol(struct rtllib_device *ieee)
{
	short ch = 0;
	int i = 0;

	rtllib_update_active_chan_map(ieee);

	if (ieee->proto_started)
		return;

	ieee->proto_started = 1;

	if (ieee->current_network.channel == 0) {
		do {
			ch++;
			if (ch > MAX_CHANNEL_NUMBER)
				return; /* no channel found */
		} while (!ieee->active_channel_map[ch]);
		ieee->current_network.channel = ch;
	}

	if (ieee->current_network.beacon_interval == 0)
		ieee->current_network.beacon_interval = 100;

	for (i = 0; i < 17; i++) {
		ieee->last_rxseq_num[i] = -1;
		ieee->last_rxfrag_num[i] = -1;
		ieee->last_packet_time[i] = 0;
	}

	if (ieee->UpdateBeaconInterruptHandler)
		ieee->UpdateBeaconInterruptHandler(ieee->dev, false);

	ieee->wmm_acm = 0;
	/* if the user set the MAC of the ad-hoc cell and then
	 * switch to managed mode, shall we  make sure that association
	 * attempts does not fail just because the user provide the essid
	 * and the nic is still checking for the AP MAC ??
	 */
	if (ieee->iw_mode == IW_MODE_INFRA) {
		rtllib_start_bss(ieee);
	} else if (ieee->iw_mode == IW_MODE_ADHOC) {
		if (ieee->UpdateBeaconInterruptHandler)
			ieee->UpdateBeaconInterruptHandler(ieee->dev, true);

		rtllib_start_ibss(ieee);

	} else if (ieee->iw_mode == IW_MODE_MASTER) {
		rtllib_start_master_bss(ieee);
	} else if (ieee->iw_mode == IW_MODE_MONITOR) {
		rtllib_start_monitor_mode(ieee);
	}
}