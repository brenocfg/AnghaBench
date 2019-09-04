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
typedef  scalar_t__ u8 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_MAX_NUMBER_5G ; 
 scalar_t__ MAX_5G_BANDWIDTH_NUM ; 
 scalar_t__ MAX_REGULATION_NUM ; 
 int /*<<< orphan*/  __rtl8822be_phy_cross_reference_core (struct ieee80211_hw*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
_rtl8822be_phy_cross_reference_ht_and_vht_txpower_limit(struct ieee80211_hw *hw)
{
	u8 regulation, bw, channel;

	for (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) {
		for (bw = 0; bw < MAX_5G_BANDWIDTH_NUM; ++bw) {
			for (channel = 0; channel < CHANNEL_MAX_NUMBER_5G;
			     ++channel) {
				__rtl8822be_phy_cross_reference_core(
					hw, regulation, bw, channel);
			}
		}
	}
}