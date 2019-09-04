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
struct ieee80211_rx_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ieee80211_verify_alignment(struct ieee80211_rx_data *rx)
{
#ifdef CONFIG_MAC80211_VERBOSE_DEBUG
	WARN_ON_ONCE((unsigned long)rx->skb->data & 1);
#endif
}