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
struct sci_sas_address {scalar_t__ low; scalar_t__ high; } ;
struct sci_port_configuration_agent {TYPE_3__* phy_valid_port_range; } ;
struct TYPE_5__ {TYPE_1__* ports; } ;
struct isci_host {int /*<<< orphan*/ * phys; int /*<<< orphan*/ * ports; TYPE_2__ oem_parameters; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
struct TYPE_6__ {size_t min_index; size_t max_index; } ;
struct TYPE_4__ {int phy_mask; } ;

/* Variables and functions */
 int SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION ; 
 size_t SCI_MAX_PHYS ; 
 size_t SCI_MAX_PORTS ; 
 int /*<<< orphan*/  sci_phy_get_sas_address (int /*<<< orphan*/ *,struct sci_sas_address*) ; 
 int /*<<< orphan*/  sci_port_add_phy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sci_port_configuration_agent_validate_ports (struct isci_host*,struct sci_port_configuration_agent*) ; 
 scalar_t__ sci_sas_address_compare (struct sci_sas_address,struct sci_sas_address) ; 

__attribute__((used)) static enum sci_status
sci_mpc_agent_validate_phy_configuration(struct isci_host *ihost,
					      struct sci_port_configuration_agent *port_agent)
{
	u32 phy_mask;
	u32 assigned_phy_mask;
	struct sci_sas_address sas_address;
	struct sci_sas_address phy_assigned_address;
	u8 port_index;
	u8 phy_index;

	assigned_phy_mask = 0;
	sas_address.high = 0;
	sas_address.low = 0;

	for (port_index = 0; port_index < SCI_MAX_PORTS; port_index++) {
		phy_mask = ihost->oem_parameters.ports[port_index].phy_mask;

		if (!phy_mask)
			continue;
		/*
		 * Make sure that one or more of the phys were not already assinged to
		 * a different port. */
		if ((phy_mask & ~assigned_phy_mask) == 0) {
			return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
		}

		/* Find the starting phy index for this round through the loop */
		for (phy_index = 0; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask & (1 << phy_index)) == 0)
				continue;
			sci_phy_get_sas_address(&ihost->phys[phy_index],
						     &sas_address);

			/*
			 * The phy_index can be used as the starting point for the
			 * port range since the hardware starts all logical ports
			 * the same as the PE index. */
			port_agent->phy_valid_port_range[phy_index].min_index = port_index;
			port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

			if (phy_index != port_index) {
				return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
			}

			break;
		}

		/*
		 * See how many additional phys are being added to this logical port.
		 * Note: We have not moved the current phy_index so we will actually
		 *       compare the startting phy with itself.
		 *       This is expected and required to add the phy to the port. */
		for (; phy_index < SCI_MAX_PHYS; phy_index++) {
			if ((phy_mask & (1 << phy_index)) == 0)
				continue;
			sci_phy_get_sas_address(&ihost->phys[phy_index],
						     &phy_assigned_address);

			if (sci_sas_address_compare(sas_address, phy_assigned_address) != 0) {
				/*
				 * The phy mask specified that this phy is part of the same port
				 * as the starting phy and it is not so fail this configuration */
				return SCI_FAILURE_UNSUPPORTED_PORT_CONFIGURATION;
			}

			port_agent->phy_valid_port_range[phy_index].min_index = port_index;
			port_agent->phy_valid_port_range[phy_index].max_index = phy_index;

			sci_port_add_phy(&ihost->ports[port_index],
					      &ihost->phys[phy_index]);

			assigned_phy_mask |= (1 << phy_index);
		}

	}

	return sci_port_configuration_agent_validate_ports(ihost, port_agent);
}