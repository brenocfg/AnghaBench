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
struct ieee80211_rx_data {int /*<<< orphan*/  sta; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  test_sta_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ieee80211_802_1x_port_control(struct ieee80211_rx_data *rx)
{
	if (unlikely(!rx->sta || !test_sta_flag(rx->sta, WLAN_STA_AUTHORIZED)))
		return -EACCES;

	return 0;
}