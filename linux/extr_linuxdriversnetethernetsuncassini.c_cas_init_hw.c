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
struct cas {scalar_t__ lstate; int /*<<< orphan*/  dev; scalar_t__ timer_ticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_begin_auto_negotiation (struct cas*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cas_init_dma (struct cas*) ; 
 int /*<<< orphan*/  cas_init_mac (struct cas*) ; 
 int /*<<< orphan*/  cas_init_pause_thresholds (struct cas*) ; 
 int /*<<< orphan*/  cas_phy_init (struct cas*) ; 
 int /*<<< orphan*/  cas_set_link_modes (struct cas*) ; 
 scalar_t__ link_up ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cas_init_hw(struct cas *cp, int restart_link)
{
	if (restart_link)
		cas_phy_init(cp);

	cas_init_pause_thresholds(cp);
	cas_init_mac(cp);
	cas_init_dma(cp);

	if (restart_link) {
		/* Default aneg parameters */
		cp->timer_ticks = 0;
		cas_begin_auto_negotiation(cp, NULL);
	} else if (cp->lstate == link_up) {
		cas_set_link_modes(cp);
		netif_carrier_on(cp->dev);
	}
}