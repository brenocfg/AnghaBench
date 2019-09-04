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
struct TYPE_2__ {int /*<<< orphan*/  position; int /*<<< orphan*/  membership; } ;
struct ieee80211_bss_conf {TYPE_1__ mu_group; } ;
struct ieee80211_vif {int /*<<< orphan*/  mu_mimo_owner; struct ieee80211_bss_conf bss_conf; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WLAN_MEMBERSHIP_LEN ; 
 int /*<<< orphan*/  WLAN_USER_POSITION_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void ieee80211_update_mu_groups(struct ieee80211_vif *vif,
				const u8 *membership, const u8 *position)
{
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

	if (WARN_ON_ONCE(!vif->mu_mimo_owner))
		return;

	memcpy(bss_conf->mu_group.membership, membership, WLAN_MEMBERSHIP_LEN);
	memcpy(bss_conf->mu_group.position, position, WLAN_USER_POSITION_LEN);
}