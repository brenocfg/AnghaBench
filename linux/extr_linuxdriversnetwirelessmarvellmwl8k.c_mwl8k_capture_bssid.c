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
struct mwl8k_priv {int /*<<< orphan*/  capture_bssid; scalar_t__ capture_beacon; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mwl8k_capture_bssid(struct mwl8k_priv *priv, struct ieee80211_hdr *wh)
{
	return priv->capture_beacon &&
		ieee80211_is_beacon(wh->frame_control) &&
		ether_addr_equal_64bits(wh->addr3, priv->capture_bssid);
}