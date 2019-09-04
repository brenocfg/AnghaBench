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
typedef  int u8 ;
struct sas_phy {void* minimum_linkrate; void* maximum_linkrate; void* minimum_linkrate_hw; void* maximum_linkrate_hw; void* negotiated_linkrate; } ;
struct TYPE_2__ {void* linkrate; struct sas_phy* phy; } ;
struct pm8001_phy {TYPE_1__ sas_phy; } ;

/* Variables and functions */
#define  PHY_SPEED_120 131 
#define  PHY_SPEED_15 130 
#define  PHY_SPEED_30 129 
#define  PHY_SPEED_60 128 
 void* SAS_LINK_RATE_12_0_GBPS ; 
 void* SAS_LINK_RATE_1_5_GBPS ; 
 void* SAS_LINK_RATE_3_0_GBPS ; 
 void* SAS_LINK_RATE_6_0_GBPS ; 

void pm8001_get_lrate_mode(struct pm8001_phy *phy, u8 link_rate)
{
	struct sas_phy *sas_phy = phy->sas_phy.phy;

	switch (link_rate) {
	case PHY_SPEED_120:
		phy->sas_phy.linkrate = SAS_LINK_RATE_12_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_12_0_GBPS;
		break;
	case PHY_SPEED_60:
		phy->sas_phy.linkrate = SAS_LINK_RATE_6_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_6_0_GBPS;
		break;
	case PHY_SPEED_30:
		phy->sas_phy.linkrate = SAS_LINK_RATE_3_0_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_3_0_GBPS;
		break;
	case PHY_SPEED_15:
		phy->sas_phy.linkrate = SAS_LINK_RATE_1_5_GBPS;
		phy->sas_phy.phy->negotiated_linkrate = SAS_LINK_RATE_1_5_GBPS;
		break;
	}
	sas_phy->negotiated_linkrate = phy->sas_phy.linkrate;
	sas_phy->maximum_linkrate_hw = SAS_LINK_RATE_6_0_GBPS;
	sas_phy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
	sas_phy->maximum_linkrate = SAS_LINK_RATE_6_0_GBPS;
	sas_phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
}