#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ cstate_t ;

/* Variables and functions */
 size_t NBP1 ; 
 int PCI_MONITOR_ENABLE_REG ; 
 int PCI_NBP1_ACTIVE_BIT ; 
 int PCI_NBP1_ENTERED_BIT ; 
 int amd_fam14h_get_pci_info (TYPE_1__*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  amd_fam14h_pci_dev ; 
 int** current_count ; 
 int /*<<< orphan*/  dprint (char*,char*,int,unsigned int,...) ; 
 int nbp1_entered ; 
 int pci_read_long (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_long (int /*<<< orphan*/ ,int,int) ; 
 int** previous_count ; 

__attribute__((used)) static int amd_fam14h_disable(cstate_t *state, unsigned int cpu)
{
	int enable_bit, pci_offset, ret;
	uint32_t val;

	ret = amd_fam14h_get_pci_info(state, &pci_offset, &enable_bit, cpu);
	if (ret)
		return ret;

	val = pci_read_long(amd_fam14h_pci_dev, pci_offset);
	dprint("%s: offset: 0x%x %u\n", state->name, pci_offset, val);
	if (state->id == NBP1) {
		/* was the bit whether NBP1 got entered set? */
		nbp1_entered = (val & (1 << PCI_NBP1_ACTIVE_BIT)) |
			(val & (1 << PCI_NBP1_ENTERED_BIT));

		dprint("NBP1 was %sentered - 0x%x - enable_bit: "
		       "%d - pci_offset: 0x%x\n",
		       nbp1_entered ? "" : "not ",
		       val, enable_bit, pci_offset);
		return ret;
	}
	current_count[state->id][cpu] = val;

	dprint("%s: Current -  %llu (%u)\n", state->name,
	       current_count[state->id][cpu], cpu);
	dprint("%s: Previous - %llu (%u)\n", state->name,
	       previous_count[state->id][cpu], cpu);

	val = pci_read_long(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG);
	val &= ~(1 << enable_bit);
	pci_write_long(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG, val);

	return 0;
}