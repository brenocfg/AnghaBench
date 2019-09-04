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
typedef  int /*<<< orphan*/  u8 ;
struct sas_ha_struct {int dummy; } ;
struct asd_sas_phy {int enabled; int id; struct pm8001_phy* lldd_phy; struct sas_ha_struct* ha; int /*<<< orphan*/ * frame_rcvd; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  linkrate; int /*<<< orphan*/  oob_mode; int /*<<< orphan*/  role; int /*<<< orphan*/  type; scalar_t__ tproto; int /*<<< orphan*/  iproto; int /*<<< orphan*/  class; } ;
struct pm8001_phy {int /*<<< orphan*/ * frame_rcvd; int /*<<< orphan*/  dev_sas_addr; struct pm8001_hba_info* pm8001_ha; scalar_t__ phy_state; struct asd_sas_phy sas_phy; } ;
struct pm8001_hba_info {TYPE_2__* shost; TYPE_1__* chip; struct pm8001_phy* phy; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;
struct TYPE_3__ {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OOB_NOT_CONNECTED ; 
 int /*<<< orphan*/  PHY_ROLE_INITIATOR ; 
 int /*<<< orphan*/  PHY_TYPE_PHYSICAL ; 
 int /*<<< orphan*/  SAS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 

__attribute__((used)) static void pm8001_phy_init(struct pm8001_hba_info *pm8001_ha, int phy_id)
{
	struct pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	struct asd_sas_phy *sas_phy = &phy->sas_phy;
	phy->phy_state = 0;
	phy->pm8001_ha = pm8001_ha;
	sas_phy->enabled = (phy_id < pm8001_ha->chip->n_phy) ? 1 : 0;
	sas_phy->class = SAS;
	sas_phy->iproto = SAS_PROTOCOL_ALL;
	sas_phy->tproto = 0;
	sas_phy->type = PHY_TYPE_PHYSICAL;
	sas_phy->role = PHY_ROLE_INITIATOR;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->linkrate = SAS_LINK_RATE_UNKNOWN;
	sas_phy->id = phy_id;
	sas_phy->sas_addr = (u8 *)&phy->dev_sas_addr;
	sas_phy->frame_rcvd = &phy->frame_rcvd[0];
	sas_phy->ha = (struct sas_ha_struct *)pm8001_ha->shost->hostdata;
	sas_phy->lldd_phy = phy;
}