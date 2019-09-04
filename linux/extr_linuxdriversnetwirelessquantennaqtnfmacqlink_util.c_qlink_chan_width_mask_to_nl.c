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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_10 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_160 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_40 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_80 ; 
 int /*<<< orphan*/  NL80211_CHAN_WIDTH_80P80 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_10 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_160 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_20_NOHT ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_40 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_80 ; 
 int /*<<< orphan*/  QLINK_CHAN_WIDTH_80P80 ; 

u8 qlink_chan_width_mask_to_nl(u16 qlink_mask)
{
	u8 result = 0;

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_5))
		result |= BIT(NL80211_CHAN_WIDTH_5);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_10))
		result |= BIT(NL80211_CHAN_WIDTH_10);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_20_NOHT))
		result |= BIT(NL80211_CHAN_WIDTH_20_NOHT);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_20))
		result |= BIT(NL80211_CHAN_WIDTH_20);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_40))
		result |= BIT(NL80211_CHAN_WIDTH_40);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_80))
		result |= BIT(NL80211_CHAN_WIDTH_80);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_80P80))
		result |= BIT(NL80211_CHAN_WIDTH_80P80);

	if (qlink_mask & BIT(QLINK_CHAN_WIDTH_160))
		result |= BIT(NL80211_CHAN_WIDTH_160);

	return result;
}