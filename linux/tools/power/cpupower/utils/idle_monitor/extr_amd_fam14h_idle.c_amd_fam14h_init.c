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
 int amd_fam14h_get_pci_info (TYPE_1__*,int*,int*,unsigned int) ; 
 int /*<<< orphan*/  amd_fam14h_pci_dev ; 
 int /*<<< orphan*/  dprint (char*,int /*<<< orphan*/ ,int,int,...) ; 
 int pci_read_long (int /*<<< orphan*/ ,int) ; 
 int pci_write_long (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__** previous_count ; 

__attribute__((used)) static int amd_fam14h_init(cstate_t *state, unsigned int cpu)
{
	int enable_bit, pci_offset, ret;
	uint32_t val;

	ret = amd_fam14h_get_pci_info(state, &pci_offset, &enable_bit, cpu);
	if (ret)
		return ret;

	/* NBP1 needs extra treating -> write 1 to D18F6x98 bit 1 for init */
	if (state->id == NBP1) {
		val = pci_read_long(amd_fam14h_pci_dev, pci_offset);
		val |= 1 << enable_bit;
		val = pci_write_long(amd_fam14h_pci_dev, pci_offset, val);
		return ret;
	}

	/* Enable monitor */
	val = pci_read_long(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG);
	dprint("Init %s: read at offset: 0x%x val: %u\n", state->name,
	       PCI_MONITOR_ENABLE_REG, (unsigned int) val);
	val |= 1 << enable_bit;
	pci_write_long(amd_fam14h_pci_dev, PCI_MONITOR_ENABLE_REG, val);

	dprint("Init %s: offset: 0x%x enable_bit: %d - val: %u (%u)\n",
	       state->name, PCI_MONITOR_ENABLE_REG, enable_bit,
	       (unsigned int) val, cpu);

	/* Set counter to zero */
	pci_write_long(amd_fam14h_pci_dev, pci_offset, 0);
	previous_count[state->id][cpu] = 0;

	return 0;
}