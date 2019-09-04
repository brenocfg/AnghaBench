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
struct asd_phy_desc {int max_sas_lrate; int min_sas_lrate; int max_sata_lrate; int min_sata_lrate; } ;

/* Variables and functions */
#define  SAS_LINK_RATE_1_5_GBPS 130 
#define  SAS_LINK_RATE_3_0_GBPS 129 
#define  SAS_LINK_RATE_6_0_GBPS 128 
 int SAS_SPEED_15_DIS ; 
 int SAS_SPEED_30_DIS ; 
 int SAS_SPEED_60_DIS ; 
 int SATA_SPEED_15_DIS ; 
 int SATA_SPEED_30_DIS ; 

__attribute__((used)) static void set_speed_mask(u8 *speed_mask, struct asd_phy_desc *pd)
{
	/* disable all speeds, then enable defaults */
	*speed_mask = SAS_SPEED_60_DIS | SAS_SPEED_30_DIS | SAS_SPEED_15_DIS
		| SATA_SPEED_30_DIS | SATA_SPEED_15_DIS;

	switch (pd->max_sas_lrate) {
	case SAS_LINK_RATE_6_0_GBPS:
		*speed_mask &= ~SAS_SPEED_60_DIS;
	default:
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SAS_SPEED_30_DIS;
	case SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SAS_SPEED_15_DIS;
	}

	switch (pd->min_sas_lrate) {
	case SAS_LINK_RATE_6_0_GBPS:
		*speed_mask |= SAS_SPEED_30_DIS;
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SAS_SPEED_15_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:
		/* nothing to do */
		;
	}

	switch (pd->max_sata_lrate) {
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask &= ~SATA_SPEED_30_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:
		*speed_mask &= ~SATA_SPEED_15_DIS;
	}

	switch (pd->min_sata_lrate) {
	case SAS_LINK_RATE_3_0_GBPS:
		*speed_mask |= SATA_SPEED_15_DIS;
	default:
	case SAS_LINK_RATE_1_5_GBPS:
		/* nothing to do */
		;
	}
}