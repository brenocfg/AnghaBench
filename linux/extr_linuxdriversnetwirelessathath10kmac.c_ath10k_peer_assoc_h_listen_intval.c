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
typedef  int u32 ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ath10k {TYPE_2__* hw; } ;
struct TYPE_3__ {int listen_interval; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 

__attribute__((used)) static u32 ath10k_peer_assoc_h_listen_intval(struct ath10k *ar,
					     struct ieee80211_vif *vif)
{
	/* Some firmware revisions have unstable STA powersave when listen
	 * interval is set too high (e.g. 5). The symptoms are firmware doesn't
	 * generate NullFunc frames properly even if buffered frames have been
	 * indicated in Beacon TIM. Firmware would seldom wake up to pull
	 * buffered frames. Often pinging the device from AP would simply fail.
	 *
	 * As a workaround set it to 1.
	 */
	if (vif->type == NL80211_IFTYPE_STATION)
		return 1;

	return ar->hw->conf.listen_interval;
}