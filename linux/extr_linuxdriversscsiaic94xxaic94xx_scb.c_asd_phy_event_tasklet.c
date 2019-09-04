#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_phy_event ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct done_list_struct {int* status_block; } ;
struct TYPE_6__ {int /*<<< orphan*/  iproto; int /*<<< orphan*/  linkrate; } ;
struct asd_phy {TYPE_1__ sas_phy; } ;
struct asd_ha_struct {struct asd_phy* phys; struct sas_ha_struct sas_ha; } ;
struct asd_ascb {struct asd_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,int,...) ; 
#define  CURRENT_GTO_TIMEOUT 132 
#define  CURRENT_LOSS_OF_SIGNAL 131 
#define  CURRENT_OOB_DONE 130 
#define  CURRENT_OOB_ERROR 129 
#define  CURRENT_SPINUP_HOLD 128 
 int DL_PHY_MASK ; 
 int /*<<< orphan*/  PHYE_LOSS_OF_SIGNAL ; 
 int /*<<< orphan*/  PHYE_OOB_DONE ; 
 int /*<<< orphan*/  PHYE_OOB_ERROR ; 
 int /*<<< orphan*/  PHYE_SPINUP_HOLD ; 
 int PHY_EVENTS_STATUS ; 
 int /*<<< orphan*/  asd_turn_led (struct asd_ha_struct*,int,int) ; 
 int /*<<< orphan*/  get_lrate_mode (struct asd_phy*,int) ; 
 int /*<<< orphan*/  sas_phy_disconnected (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asd_phy_event_tasklet(struct asd_ascb *ascb,
					 struct done_list_struct *dl)
{
	struct asd_ha_struct *asd_ha = ascb->ha;
	struct sas_ha_struct *sas_ha = &asd_ha->sas_ha;
	int phy_id = dl->status_block[0] & DL_PHY_MASK;
	struct asd_phy *phy = &asd_ha->phys[phy_id];

	u8 oob_status = dl->status_block[1] & PHY_EVENTS_STATUS;
	u8 oob_mode   = dl->status_block[2];

	switch (oob_status) {
	case CURRENT_LOSS_OF_SIGNAL:
		/* directly attached device was removed */
		ASD_DPRINTK("phy%d: device unplugged\n", phy_id);
		asd_turn_led(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_LOSS_OF_SIGNAL);
		break;
	case CURRENT_OOB_DONE:
		/* hot plugged device */
		asd_turn_led(asd_ha, phy_id, 1);
		get_lrate_mode(phy, oob_mode);
		ASD_DPRINTK("phy%d device plugged: lrate:0x%x, proto:0x%x\n",
			    phy_id, phy->sas_phy.linkrate, phy->sas_phy.iproto);
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_OOB_DONE);
		break;
	case CURRENT_SPINUP_HOLD:
		/* hot plug SATA, no COMWAKE sent */
		asd_turn_led(asd_ha, phy_id, 1);
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_SPINUP_HOLD);
		break;
	case CURRENT_GTO_TIMEOUT:
	case CURRENT_OOB_ERROR:
		ASD_DPRINTK("phy%d error while OOB: oob status:0x%x\n", phy_id,
			    dl->status_block[1]);
		asd_turn_led(asd_ha, phy_id, 0);
		sas_phy_disconnected(&phy->sas_phy);
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_OOB_ERROR);
		break;
	}
}