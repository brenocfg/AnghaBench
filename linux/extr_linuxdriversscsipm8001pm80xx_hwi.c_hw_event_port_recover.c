#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct pm8001_port {unsigned int wide_port_phymap; } ;
struct TYPE_4__ {int /*<<< orphan*/  oob_mode; } ;
struct pm8001_phy {int phy_attached; int /*<<< orphan*/  phy_state; TYPE_2__ sas_phy; } ;
struct pm8001_hba_info {struct pm8001_port* port; struct pm8001_phy* phy; } ;
struct TYPE_3__ {size_t dev_type; } ;
struct hw_event_resp {TYPE_1__ sas_identify; int /*<<< orphan*/  lr_status_evt_portid; int /*<<< orphan*/  phyid_npip_portstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_NOTIFY_ENABLE_SPINUP ; 
 int /*<<< orphan*/  PHY_STATE_LINK_UP_SPCV ; 
 size_t SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_OOB_MODE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_get_lrate_mode (struct pm8001_phy*,size_t) ; 
 int /*<<< orphan*/  pm80xx_chip_phy_ctl_req (struct pm8001_hba_info*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_event_port_recover(struct pm8001_hba_info *pm8001_ha,
					void *piomb)
{
	struct hw_event_resp *pPayload = (struct hw_event_resp *)(piomb + 4);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u8 phy_id = (u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u8 deviceType = pPayload->sas_identify.dev_type;
	u8 link_rate = (u8)((lr_status_evt_portid & 0xF0000000) >> 28);
	struct pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	struct pm8001_port *port = &pm8001_ha->port[port_id];

	if (deviceType == SAS_END_DEVICE) {
		pm80xx_chip_phy_ctl_req(pm8001_ha, phy_id,
					PHY_NOTIFY_ENABLE_SPINUP);
	}

	port->wide_port_phymap |= (1U << phy_id);
	pm8001_get_lrate_mode(phy, link_rate);
	phy->sas_phy.oob_mode = SAS_OOB_MODE;
	phy->phy_state = PHY_STATE_LINK_UP_SPCV;
	phy->phy_attached = 1;
}