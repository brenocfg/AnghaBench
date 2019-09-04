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
struct zd_mac {scalar_t__ type; TYPE_1__* vif; int /*<<< orphan*/  chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 int set_rx_filter (struct zd_mac*) ; 
 int zd_write_bssid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zd_write_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_mac_and_bssid(struct zd_mac *mac)
{
	int r;

	if (!mac->vif)
		return -1;

	r = zd_write_mac_addr(&mac->chip, mac->vif->addr);
	if (r)
		return r;

	/* Vendor driver after setting MAC either sets BSSID for AP or
	 * filter for other modes.
	 */
	if (mac->type != NL80211_IFTYPE_AP)
		return set_rx_filter(mac);
	else
		return zd_write_bssid(&mac->chip, mac->vif->addr);
}