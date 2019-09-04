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
struct asd_ha_struct {TYPE_1__* io_handle; int /*<<< orphan*/  pcidev; } ;
struct TYPE_2__ {int swb_base; } ;

/* Variables and functions */
 int MBAR0_SWB_SIZE ; 
 int /*<<< orphan*/  PCI_CONF_MBAR0_SWB ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void asd_move_swb(struct asd_ha_struct *asd_ha, u32 reg)
{
	u32 base = reg & ~(MBAR0_SWB_SIZE-1);
	pci_write_config_dword(asd_ha->pcidev, PCI_CONF_MBAR0_SWB, base);
	asd_ha->io_handle[0].swb_base = base;
}