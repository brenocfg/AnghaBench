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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct sci_oem_params {TYPE_2__* phys; } ;
struct TYPE_6__ {int enabled; int id; int /*<<< orphan*/  linkrate; int /*<<< orphan*/  oob_mode; int /*<<< orphan*/  role; int /*<<< orphan*/  type; scalar_t__ tproto; int /*<<< orphan*/  iproto; int /*<<< orphan*/  class; struct isci_phy* lldd_phy; int /*<<< orphan*/ * ha; int /*<<< orphan*/ * frame_rcvd; int /*<<< orphan*/ * sas_addr; } ;
struct isci_phy {int /*<<< orphan*/  frame_rcvd; TYPE_3__ sas_phy; int /*<<< orphan*/ * sas_addr; } ;
struct isci_host {int /*<<< orphan*/  sas_ha; struct sci_oem_params oem_parameters; } ;
typedef  int /*<<< orphan*/  sas_addr ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {int high; int low; } ;
struct TYPE_5__ {TYPE_1__ sas_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  OOB_NOT_CONNECTED ; 
 int /*<<< orphan*/  PHY_ROLE_INITIATOR ; 
 int /*<<< orphan*/  PHY_TYPE_PHYSICAL ; 
 int /*<<< orphan*/  SAS ; 
 int /*<<< orphan*/  SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PROTOCOL_ALL ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void isci_phy_init(struct isci_phy *iphy, struct isci_host *ihost, int index)
{
	struct sci_oem_params *oem = &ihost->oem_parameters;
	u64 sci_sas_addr;
	__be64 sas_addr;

	sci_sas_addr = oem->phys[index].sas_address.high;
	sci_sas_addr <<= 32;
	sci_sas_addr |= oem->phys[index].sas_address.low;
	sas_addr = cpu_to_be64(sci_sas_addr);
	memcpy(iphy->sas_addr, &sas_addr, sizeof(sas_addr));

	iphy->sas_phy.enabled = 0;
	iphy->sas_phy.id = index;
	iphy->sas_phy.sas_addr = &iphy->sas_addr[0];
	iphy->sas_phy.frame_rcvd = (u8 *)&iphy->frame_rcvd;
	iphy->sas_phy.ha = &ihost->sas_ha;
	iphy->sas_phy.lldd_phy = iphy;
	iphy->sas_phy.enabled = 1;
	iphy->sas_phy.class = SAS;
	iphy->sas_phy.iproto = SAS_PROTOCOL_ALL;
	iphy->sas_phy.tproto = 0;
	iphy->sas_phy.type = PHY_TYPE_PHYSICAL;
	iphy->sas_phy.role = PHY_ROLE_INITIATOR;
	iphy->sas_phy.oob_mode = OOB_NOT_CONNECTED;
	iphy->sas_phy.linkrate = SAS_LINK_RATE_UNKNOWN;
	memset(&iphy->frame_rcvd, 0, sizeof(iphy->frame_rcvd));
}