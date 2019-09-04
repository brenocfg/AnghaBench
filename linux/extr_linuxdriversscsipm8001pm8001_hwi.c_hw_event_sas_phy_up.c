#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct sas_identify_frame {int dummy; } ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_phy_event ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct pm8001_port {size_t port_state; int port_attached; } ;
struct TYPE_5__ {int /*<<< orphan*/  frame_rcvd_lock; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  oob_mode; } ;
struct TYPE_4__ {size_t device_type; int /*<<< orphan*/  target_port_protocols; } ;
struct pm8001_phy {int phy_attached; int frame_rcvd_size; TYPE_2__ sas_phy; int /*<<< orphan*/  frame_rcvd; TYPE_1__ identify; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  phy_state; } ;
struct pm8001_hba_info {scalar_t__ flags; struct pm8001_phy* phy; struct sas_ha_struct* sas; struct pm8001_port* port; } ;
struct TYPE_6__ {size_t dev_type; } ;
struct hw_event_resp {TYPE_3__ sas_identify; int /*<<< orphan*/  npip_portstate; int /*<<< orphan*/  lr_evt_status_phyid_portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYE_OOB_DONE ; 
 int /*<<< orphan*/  PHY_NOTIFY_ENABLE_SPINUP ; 
 int /*<<< orphan*/  PHY_STATE_LINK_UP_SPC ; 
 scalar_t__ PM8001F_RUN_TIME ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_TYPE_SAS ; 
#define  SAS_EDGE_EXPANDER_DEVICE 131 
#define  SAS_END_DEVICE 130 
#define  SAS_FANOUT_EXPANDER_DEVICE 129 
 int /*<<< orphan*/  SAS_OOB_MODE ; 
#define  SAS_PHY_UNUSED 128 
 int /*<<< orphan*/  SAS_PROTOCOL_SMP ; 
 int /*<<< orphan*/  SAS_PROTOCOL_SSP ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pm8001_bytes_dmaed (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_chip_phy_ctl_req (struct pm8001_hba_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_get_attached_sas_addr (struct pm8001_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_get_lrate_mode (struct pm8001_phy*,size_t) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hw_event_sas_phy_up(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct hw_event_resp *pPayload =
		(struct hw_event_resp *)(piomb + 4);
	u32 lr_evt_status_phyid_portid =
		le32_to_cpu(pPayload->lr_evt_status_phyid_portid);
	u8 link_rate =
		(u8)((lr_evt_status_phyid_portid & 0xF0000000) >> 28);
	u8 port_id = (u8)(lr_evt_status_phyid_portid & 0x0000000F);
	u8 phy_id =
		(u8)((lr_evt_status_phyid_portid & 0x000000F0) >> 4);
	u32 npip_portstate = le32_to_cpu(pPayload->npip_portstate);
	u8 portstate = (u8)(npip_portstate & 0x0000000F);
	struct pm8001_port *port = &pm8001_ha->port[port_id];
	struct sas_ha_struct *sas_ha = pm8001_ha->sas;
	struct pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	unsigned long flags;
	u8 deviceType = pPayload->sas_identify.dev_type;
	port->port_state =  portstate;
	phy->phy_state = PHY_STATE_LINK_UP_SPC;
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk("HW_EVENT_SAS_PHY_UP port id = %d, phy id = %d\n",
		port_id, phy_id));

	switch (deviceType) {
	case SAS_PHY_UNUSED:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("device type no device.\n"));
		break;
	case SAS_END_DEVICE:
		PM8001_MSG_DBG(pm8001_ha, pm8001_printk("end device.\n"));
		pm8001_chip_phy_ctl_req(pm8001_ha, phy_id,
			PHY_NOTIFY_ENABLE_SPINUP);
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		break;
	case SAS_EDGE_EXPANDER_DEVICE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("expander device.\n"));
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		break;
	case SAS_FANOUT_EXPANDER_DEVICE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("fanout expander device.\n"));
		port->port_attached = 1;
		pm8001_get_lrate_mode(phy, link_rate);
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("unknown device type(%x)\n", deviceType));
		break;
	}
	phy->phy_type |= PORT_TYPE_SAS;
	phy->identify.device_type = deviceType;
	phy->phy_attached = 1;
	if (phy->identify.device_type == SAS_END_DEVICE)
		phy->identify.target_port_protocols = SAS_PROTOCOL_SSP;
	else if (phy->identify.device_type != SAS_PHY_UNUSED)
		phy->identify.target_port_protocols = SAS_PROTOCOL_SMP;
	phy->sas_phy.oob_mode = SAS_OOB_MODE;
	sas_ha->notify_phy_event(&phy->sas_phy, PHYE_OOB_DONE);
	spin_lock_irqsave(&phy->sas_phy.frame_rcvd_lock, flags);
	memcpy(phy->frame_rcvd, &pPayload->sas_identify,
		sizeof(struct sas_identify_frame)-4);
	phy->frame_rcvd_size = sizeof(struct sas_identify_frame) - 4;
	pm8001_get_attached_sas_addr(phy, phy->sas_phy.attached_sas_addr);
	spin_unlock_irqrestore(&phy->sas_phy.frame_rcvd_lock, flags);
	if (pm8001_ha->flags == PM8001F_RUN_TIME)
		mdelay(200);/*delay a moment to wait disk to spinup*/
	pm8001_bytes_dmaed(pm8001_ha, phy_id);
}