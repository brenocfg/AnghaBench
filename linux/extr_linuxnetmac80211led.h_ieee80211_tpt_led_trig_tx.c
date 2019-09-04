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
struct ieee80211_local {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */

__attribute__((used)) static inline void
ieee80211_tpt_led_trig_tx(struct ieee80211_local *local, __le16 fc, int bytes)
{
#ifdef CONFIG_MAC80211_LEDS
	if (ieee80211_is_data(fc) && atomic_read(&local->tpt_led_active))
		local->tpt_led_trigger->tx_bytes += bytes;
#endif
}