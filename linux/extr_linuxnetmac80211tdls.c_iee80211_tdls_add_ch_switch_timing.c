#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_ch_switch_timing {void* switch_timeout; void* switch_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_CHAN_SWITCH_TIMING ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iee80211_tdls_add_ch_switch_timing(u8 *buf, u16 switch_time, u16 switch_timeout)
{
	struct ieee80211_ch_switch_timing *ch_sw;

	*buf++ = WLAN_EID_CHAN_SWITCH_TIMING;
	*buf++ = sizeof(struct ieee80211_ch_switch_timing);

	ch_sw = (void *)buf;
	ch_sw->switch_time = cpu_to_le16(switch_time);
	ch_sw->switch_timeout = cpu_to_le16(switch_timeout);
}