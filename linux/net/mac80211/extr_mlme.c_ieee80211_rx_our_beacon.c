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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_bss {TYPE_1__* transmitted_bss; int /*<<< orphan*/  bssid; } ;
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_rx_our_beacon(const u8 *tx_bssid,
				    struct cfg80211_bss *bss)
{
	if (ether_addr_equal(tx_bssid, bss->bssid))
		return true;
	if (!bss->transmitted_bss)
		return false;
	return ether_addr_equal(tx_bssid, bss->transmitted_bss->bssid);
}