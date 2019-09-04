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
struct sas_identify {void* target_port_protocols; void* initiator_port_protocols; int /*<<< orphan*/  device_type; int /*<<< orphan*/  sas_address; } ;
struct sas_phy {void* negotiated_linkrate; void* maximum_linkrate; void* minimum_linkrate; void* maximum_linkrate_hw; void* minimum_linkrate_hw; struct sas_identify identify; } ;
struct hpsa_sas_port {int /*<<< orphan*/  phy_list_head; int /*<<< orphan*/  port; int /*<<< orphan*/  sas_address; } ;
struct hpsa_sas_phy {int added_to_port; int /*<<< orphan*/  phy_list_entry; struct sas_phy* phy; struct hpsa_sas_port* parent_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 void* SAS_LINK_RATE_UNKNOWN ; 
 void* SAS_PROTOCOL_STP ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct sas_identify*,int /*<<< orphan*/ ,int) ; 
 int sas_phy_add (struct sas_phy*) ; 
 int /*<<< orphan*/  sas_port_add_phy (int /*<<< orphan*/ ,struct sas_phy*) ; 

__attribute__((used)) static int hpsa_sas_port_add_phy(struct hpsa_sas_phy *hpsa_sas_phy)
{
	int rc;
	struct hpsa_sas_port *hpsa_sas_port;
	struct sas_phy *phy;
	struct sas_identify *identify;

	hpsa_sas_port = hpsa_sas_phy->parent_port;
	phy = hpsa_sas_phy->phy;

	identify = &phy->identify;
	memset(identify, 0, sizeof(*identify));
	identify->sas_address = hpsa_sas_port->sas_address;
	identify->device_type = SAS_END_DEVICE;
	identify->initiator_port_protocols = SAS_PROTOCOL_STP;
	identify->target_port_protocols = SAS_PROTOCOL_STP;
	phy->minimum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate_hw = SAS_LINK_RATE_UNKNOWN;
	phy->minimum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->maximum_linkrate = SAS_LINK_RATE_UNKNOWN;
	phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;

	rc = sas_phy_add(hpsa_sas_phy->phy);
	if (rc)
		return rc;

	sas_port_add_phy(hpsa_sas_port->port, hpsa_sas_phy->phy);
	list_add_tail(&hpsa_sas_phy->phy_list_entry,
			&hpsa_sas_port->phy_list_head);
	hpsa_sas_phy->added_to_port = true;

	return 0;
}