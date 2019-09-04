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
struct wpan_phy {int lifs_period; int symbol_duration; int sifs_period; } ;

/* Variables and functions */
 int IEEE802154_LIFS_PERIOD ; 
 int IEEE802154_SIFS_PERIOD ; 

__attribute__((used)) static void ieee802154_setup_wpan_phy_pib(struct wpan_phy *wpan_phy)
{
	/* TODO warn on empty symbol_duration
	 * Should be done when all drivers sets this value.
	 */

	wpan_phy->lifs_period = IEEE802154_LIFS_PERIOD *
				wpan_phy->symbol_duration;
	wpan_phy->sifs_period = IEEE802154_SIFS_PERIOD *
				wpan_phy->symbol_duration;
}