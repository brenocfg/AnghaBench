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
typedef  int /*<<< orphan*/  u64 ;
struct sas_identify_frame {scalar_t__ sas_addr; } ;
struct asd_sas_phy {int linkrate; } ;
struct mvs_phy {int phy_status; int phy_type; int att_dev_info; int /*<<< orphan*/  att_dev_sas_addr; int /*<<< orphan*/  dev_info; int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; struct asd_sas_phy sas_phy; } ;
struct mvs_info {struct mvs_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYR_PHY_STAT ; 
 int PHY_NEG_SPP_PHYS_LINK_RATE_MASK ; 
 int PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET ; 
 int PORT_DEV_STP_TRGT ; 
 int PORT_TYPE_SAS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_1_5_GBPS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_6_0_GBPS ; 
 int /*<<< orphan*/  mv_dprintk (char*,int) ; 
 int /*<<< orphan*/  mvs_94xx_get_att_identify_frame (struct mvs_info*,int,struct sas_identify_frame*) ; 
 int /*<<< orphan*/  mvs_94xx_get_dev_identify_frame (struct mvs_info*,int,struct sas_identify_frame*) ; 
 int mvs_94xx_make_att_info (struct sas_identify_frame*) ; 
 int /*<<< orphan*/  mvs_94xx_make_dev_info (struct sas_identify_frame*) ; 
 int /*<<< orphan*/  mvs_write_port_cfg_addr (struct mvs_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_write_port_cfg_data (struct mvs_info*,int,int) ; 

__attribute__((used)) static void mvs_94xx_fix_phy_info(struct mvs_info *mvi, int i,
				struct sas_identify_frame *id)
{
	struct mvs_phy *phy = &mvi->phy[i];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	mv_dprintk("get all reg link rate is 0x%x\n", phy->phy_status);
	sas_phy->linkrate =
		(phy->phy_status & PHY_NEG_SPP_PHYS_LINK_RATE_MASK) >>
			PHY_NEG_SPP_PHYS_LINK_RATE_MASK_OFFSET;
	sas_phy->linkrate += 0x8;
	mv_dprintk("get link rate is %d\n", sas_phy->linkrate);
	phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
	phy->maximum_linkrate = SAS_LINK_RATE_6_0_GBPS;
	mvs_94xx_get_dev_identify_frame(mvi, i, id);
	phy->dev_info = mvs_94xx_make_dev_info(id);

	if (phy->phy_type & PORT_TYPE_SAS) {
		mvs_94xx_get_att_identify_frame(mvi, i, id);
		phy->att_dev_info = mvs_94xx_make_att_info(id);
		phy->att_dev_sas_addr = *(u64 *)id->sas_addr;
	} else {
		phy->att_dev_info = PORT_DEV_STP_TRGT | 1;
	}

	/* enable spin up bit */
	mvs_write_port_cfg_addr(mvi, i, PHYR_PHY_STAT);
	mvs_write_port_cfg_data(mvi, i, 0x04);

}