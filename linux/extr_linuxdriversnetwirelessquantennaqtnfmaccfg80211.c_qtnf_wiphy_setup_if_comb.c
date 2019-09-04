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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {size_t n_iface_combinations; int /*<<< orphan*/  interface_modes; struct ieee80211_iface_combination* iface_combinations; } ;
struct qtnf_mac_info {size_t n_if_comb; int /*<<< orphan*/  radar_detect_widths; struct ieee80211_iface_combination* if_comb; } ;
struct ieee80211_iface_combination {size_t n_limits; TYPE_1__* limits; int /*<<< orphan*/  radar_detect_widths; } ;
struct TYPE_2__ {int /*<<< orphan*/  types; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int
qtnf_wiphy_setup_if_comb(struct wiphy *wiphy, struct qtnf_mac_info *mac_info)
{
	struct ieee80211_iface_combination *if_comb;
	size_t n_if_comb;
	u16 interface_modes = 0;
	size_t i, j;

	if_comb = mac_info->if_comb;
	n_if_comb = mac_info->n_if_comb;

	if (!if_comb || !n_if_comb)
		return -ENOENT;

	for (i = 0; i < n_if_comb; i++) {
		if_comb[i].radar_detect_widths = mac_info->radar_detect_widths;

		for (j = 0; j < if_comb[i].n_limits; j++)
			interface_modes |= if_comb[i].limits[j].types;
	}

	wiphy->iface_combinations = if_comb;
	wiphy->n_iface_combinations = n_if_comb;
	wiphy->interface_modes = interface_modes;

	return 0;
}