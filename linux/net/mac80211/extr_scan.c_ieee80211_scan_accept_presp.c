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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;

/* Variables and functions */
 int NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP ; 
 int NL80211_SCAN_FLAG_RANDOM_ADDR ; 
 int ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool ieee80211_scan_accept_presp(struct ieee80211_sub_if_data *sdata,
					u32 scan_flags, const u8 *da)
{
	if (!sdata)
		return false;
	/* accept broadcast for OCE */
	if (scan_flags & NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP &&
	    is_broadcast_ether_addr(da))
		return true;
	if (scan_flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		return true;
	return ether_addr_equal(da, sdata->vif.addr);
}