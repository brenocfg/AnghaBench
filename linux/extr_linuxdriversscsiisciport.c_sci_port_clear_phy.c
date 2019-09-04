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
struct isci_port {struct isci_phy** phy_table; struct isci_host* owning_controller; } ;
struct isci_phy {size_t phy_index; } ;
struct isci_host {int /*<<< orphan*/ * ports; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int SCI_FAILURE ; 
 size_t SCI_MAX_PORTS ; 
 int SCI_SUCCESS ; 
 struct isci_port* phy_get_non_dummy_port (struct isci_phy*) ; 
 int /*<<< orphan*/  sci_phy_set_port (struct isci_phy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum sci_status sci_port_clear_phy(struct isci_port *iport, struct isci_phy *iphy)
{
	/* Make sure that this phy is part of this port */
	if (iport->phy_table[iphy->phy_index] == iphy &&
	    phy_get_non_dummy_port(iphy) == iport) {
		struct isci_host *ihost = iport->owning_controller;

		/* Yep it is assigned to this port so remove it */
		sci_phy_set_port(iphy, &ihost->ports[SCI_MAX_PORTS]);
		iport->phy_table[iphy->phy_index] = NULL;
		return SCI_SUCCESS;
	}

	return SCI_FAILURE;
}