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
struct isci_port {int enabled_phy_mask; } ;
struct isci_phy {int phy_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_phy_resume (struct isci_phy*) ; 

__attribute__((used)) static void sci_port_resume_phy(struct isci_port *iport, struct isci_phy *iphy)
{
	sci_phy_resume(iphy);
	iport->enabled_phy_mask |= 1 << iphy->phy_index;
}