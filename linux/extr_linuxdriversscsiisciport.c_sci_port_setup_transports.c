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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct isci_port {int active_phy_mask; int /*<<< orphan*/ * phy_table; } ;

/* Variables and functions */
 int SCI_MAX_PHYS ; 
 int /*<<< orphan*/  sci_phy_setup_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sci_port_setup_transports(struct isci_port *iport, u32 device_id)
{
	u8 index;

	for (index = 0; index < SCI_MAX_PHYS; index++) {
		if (iport->active_phy_mask & (1 << index))
			sci_phy_setup_transport(iport->phy_table[index], device_id);
	}
}