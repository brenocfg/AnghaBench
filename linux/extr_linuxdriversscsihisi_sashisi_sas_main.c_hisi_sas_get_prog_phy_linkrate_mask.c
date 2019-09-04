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
typedef  int u8 ;
typedef  int u16 ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;

/* Variables and functions */
 scalar_t__ SAS_LINK_RATE_1_5_GBPS ; 

u8 hisi_sas_get_prog_phy_linkrate_mask(enum sas_linkrate max)
{
	u16 rate = 0;
	int i;

	max -= SAS_LINK_RATE_1_5_GBPS;
	for (i = 0; i <= max; i++)
		rate |= 1 << (i * 2);
	return rate;
}