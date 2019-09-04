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
typedef  int u32 ;
struct sci_user_parameters {TYPE_1__* phys; } ;
struct isci_port {int physical_port_index; scalar_t__* phy_table; struct isci_host* owning_controller; } ;
struct isci_host {struct sci_user_parameters user_parameters; } ;
struct TYPE_2__ {scalar_t__ max_speed_generation; } ;

/* Variables and functions */
 int SCI_MAX_PHYS ; 

bool sci_port_is_valid_phy_assignment(struct isci_port *iport, u32 phy_index)
{
	struct isci_host *ihost = iport->owning_controller;
	struct sci_user_parameters *user = &ihost->user_parameters;

	/* Initialize to invalid value. */
	u32 existing_phy_index = SCI_MAX_PHYS;
	u32 index;

	if ((iport->physical_port_index == 1) && (phy_index != 1))
		return false;

	if (iport->physical_port_index == 3 && phy_index != 3)
		return false;

	if (iport->physical_port_index == 2 &&
	    (phy_index == 0 || phy_index == 1))
		return false;

	for (index = 0; index < SCI_MAX_PHYS; index++)
		if (iport->phy_table[index] && index != phy_index)
			existing_phy_index = index;

	/* Ensure that all of the phys in the port are capable of
	 * operating at the same maximum link rate.
	 */
	if (existing_phy_index < SCI_MAX_PHYS &&
	    user->phys[phy_index].max_speed_generation !=
	    user->phys[existing_phy_index].max_speed_generation)
		return false;

	return true;
}