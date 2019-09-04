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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_ampdu_params {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

int cw1200_ampdu_action(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif,
			struct ieee80211_ampdu_params *params)
{
	/* Aggregation is implemented fully in firmware,
	 * including block ack negotiation. Do not allow
	 * mac80211 stack to do anything: it interferes with
	 * the firmware.
	 */

	/* Note that we still need this function stubbed. */
	return -ENOTSUPP;
}