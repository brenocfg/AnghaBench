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
typedef  size_t u8 ;

/* Variables and functions */

__attribute__((used)) static void
wlc_phy_txpwr_nphy_po_apply(u8 *srom_max, u8 pwr_offset,
			    u8 rate_start, u8 rate_end)
{
	u8 rate;

	for (rate = rate_start; rate <= rate_end; rate++)
		srom_max[rate] -= 2 * pwr_offset;
}