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
struct isci_port {int active_phy_mask; } ;
struct isci_phy {int phy_index; } ;
struct isci_host {int /*<<< orphan*/  scic_lock; struct isci_port* ports; } ;
struct asd_sas_port {struct isci_port* lldd_port; } ;
struct asd_sas_phy {struct asd_sas_port* port; TYPE_1__* ha; } ;
struct TYPE_2__ {struct isci_host* lldd_ha; } ;

/* Variables and functions */
 int SCI_MAX_PORTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isci_phy* to_iphy (struct asd_sas_phy*) ; 
 int /*<<< orphan*/  wait_for_start (struct isci_host*) ; 

void isci_port_formed(struct asd_sas_phy *phy)
{
	struct isci_host *ihost = phy->ha->lldd_ha;
	struct isci_phy *iphy = to_iphy(phy);
	struct asd_sas_port *port = phy->port;
	struct isci_port *iport = NULL;
	unsigned long flags;
	int i;

	/* initial ports are formed as the driver is still initializing,
	 * wait for that process to complete
	 */
	wait_for_start(ihost);

	spin_lock_irqsave(&ihost->scic_lock, flags);
	for (i = 0; i < SCI_MAX_PORTS; i++) {
		iport = &ihost->ports[i];
		if (iport->active_phy_mask & 1 << iphy->phy_index)
			break;
	}
	spin_unlock_irqrestore(&ihost->scic_lock, flags);

	if (i >= SCI_MAX_PORTS)
		iport = NULL;

	port->lldd_port = iport;
}