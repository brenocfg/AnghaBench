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
typedef  int /*<<< orphan*/  u32 ;
struct tango_pcie {scalar_t__ base; } ;
struct pci_config_window {int /*<<< orphan*/  parent; } ;
struct pci_bus {struct pci_config_window* sysdata; } ;

/* Variables and functions */
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 scalar_t__ SMP8759_MUX ; 
 struct tango_pcie* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int pci_generic_config_read (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int smp8759_config_read(struct pci_bus *bus, unsigned int devfn,
			       int where, int size, u32 *val)
{
	struct pci_config_window *cfg = bus->sysdata;
	struct tango_pcie *pcie = dev_get_drvdata(cfg->parent);
	int ret;

	/* Reads in configuration space outside devfn 0 return garbage */
	if (devfn != 0)
		return PCIBIOS_FUNC_NOT_SUPPORTED;

	/*
	 * PCI config and MMIO accesses are muxed.  Linux doesn't have a
	 * mutual exclusion mechanism for config vs. MMIO accesses, so
	 * concurrent accesses may cause corruption.
	 */
	writel_relaxed(1, pcie->base + SMP8759_MUX);
	ret = pci_generic_config_read(bus, devfn, where, size, val);
	writel_relaxed(0, pcie->base + SMP8759_MUX);

	return ret;
}