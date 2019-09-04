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
typedef  int /*<<< orphan*/  u8 ;
struct mac80211_hwsim_addr_match_data {int ret; int /*<<< orphan*/  addr; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mac80211_hwsim_addr_iter(void *data, u8 *mac,
				     struct ieee80211_vif *vif)
{
	struct mac80211_hwsim_addr_match_data *md = data;

	if (memcmp(mac, md->addr, ETH_ALEN) == 0)
		md->ret = true;
}