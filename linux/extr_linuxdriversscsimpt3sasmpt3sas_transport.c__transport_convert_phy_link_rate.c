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
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;

/* Variables and functions */
#define  MPI25_SAS_NEG_LINK_RATE_12_0 137 
#define  MPI2_SAS_NEG_LINK_RATE_1_5 136 
#define  MPI2_SAS_NEG_LINK_RATE_3_0 135 
#define  MPI2_SAS_NEG_LINK_RATE_6_0 134 
#define  MPI2_SAS_NEG_LINK_RATE_NEGOTIATION_FAILED 133 
#define  MPI2_SAS_NEG_LINK_RATE_PHY_DISABLED 132 
#define  MPI2_SAS_NEG_LINK_RATE_PORT_SELECTOR 131 
#define  MPI2_SAS_NEG_LINK_RATE_SATA_OOB_COMPLETE 130 
#define  MPI2_SAS_NEG_LINK_RATE_SMP_RESET_IN_PROGRESS 129 
#define  MPI2_SAS_NEG_LINK_RATE_UNKNOWN_LINK_RATE 128 
 int SAS_LINK_RATE_12_0_GBPS ; 
 int SAS_LINK_RATE_1_5_GBPS ; 
 int SAS_LINK_RATE_3_0_GBPS ; 
 int SAS_LINK_RATE_6_0_GBPS ; 
 int SAS_LINK_RATE_FAILED ; 
 int SAS_LINK_RATE_UNKNOWN ; 
 int SAS_PHY_DISABLED ; 
 int SAS_PHY_RESET_IN_PROGRESS ; 
 int SAS_SATA_PORT_SELECTOR ; 

__attribute__((used)) static enum sas_linkrate
_transport_convert_phy_link_rate(u8 link_rate)
{
	enum sas_linkrate rc;

	switch (link_rate) {
	case MPI2_SAS_NEG_LINK_RATE_1_5:
		rc = SAS_LINK_RATE_1_5_GBPS;
		break;
	case MPI2_SAS_NEG_LINK_RATE_3_0:
		rc = SAS_LINK_RATE_3_0_GBPS;
		break;
	case MPI2_SAS_NEG_LINK_RATE_6_0:
		rc = SAS_LINK_RATE_6_0_GBPS;
		break;
	case MPI25_SAS_NEG_LINK_RATE_12_0:
		rc = SAS_LINK_RATE_12_0_GBPS;
		break;
	case MPI2_SAS_NEG_LINK_RATE_PHY_DISABLED:
		rc = SAS_PHY_DISABLED;
		break;
	case MPI2_SAS_NEG_LINK_RATE_NEGOTIATION_FAILED:
		rc = SAS_LINK_RATE_FAILED;
		break;
	case MPI2_SAS_NEG_LINK_RATE_PORT_SELECTOR:
		rc = SAS_SATA_PORT_SELECTOR;
		break;
	case MPI2_SAS_NEG_LINK_RATE_SMP_RESET_IN_PROGRESS:
		rc = SAS_PHY_RESET_IN_PROGRESS;
		break;

	default:
	case MPI2_SAS_NEG_LINK_RATE_SATA_OOB_COMPLETE:
	case MPI2_SAS_NEG_LINK_RATE_UNKNOWN_LINK_RATE:
		rc = SAS_LINK_RATE_UNKNOWN;
		break;
	}
	return rc;
}