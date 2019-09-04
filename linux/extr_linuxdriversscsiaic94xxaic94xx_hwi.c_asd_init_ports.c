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
struct asd_port {scalar_t__ num_phys; scalar_t__ phy_mask; int /*<<< orphan*/  attached_sas_addr; int /*<<< orphan*/  sas_addr; } ;
struct asd_ha_struct {struct asd_port* asd_ports; int /*<<< orphan*/  asd_ports_lock; } ;

/* Variables and functions */
 int ASD_MAX_PHYS ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asd_init_ports(struct asd_ha_struct *asd_ha)
{
	int i;

	spin_lock_init(&asd_ha->asd_ports_lock);
	for (i = 0; i < ASD_MAX_PHYS; i++) {
		struct asd_port *asd_port = &asd_ha->asd_ports[i];

		memset(asd_port->sas_addr, 0, SAS_ADDR_SIZE);
		memset(asd_port->attached_sas_addr, 0, SAS_ADDR_SIZE);
		asd_port->phy_mask = 0;
		asd_port->num_phys = 0;
	}
}