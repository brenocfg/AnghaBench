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
typedef  int u32 ;
struct faraday_pci {scalar_t__ base; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCI_CONFIG ; 
 int PCI_CONF_BUS (int) ; 
 int PCI_CONF_DEVICE (int /*<<< orphan*/ ) ; 
 int PCI_CONF_ENABLE ; 
 int PCI_CONF_FUNCTION (int /*<<< orphan*/ ) ; 
 int PCI_CONF_WHERE (int) ; 
 scalar_t__ PCI_DATA ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int faraday_raw_pci_write_config(struct faraday_pci *p, int bus_number,
					 unsigned int fn, int config, int size,
					 u32 value)
{
	int ret = PCIBIOS_SUCCESSFUL;

	writel(PCI_CONF_BUS(bus_number) |
			PCI_CONF_DEVICE(PCI_SLOT(fn)) |
			PCI_CONF_FUNCTION(PCI_FUNC(fn)) |
			PCI_CONF_WHERE(config) |
			PCI_CONF_ENABLE,
			p->base + PCI_CONFIG);

	switch (size) {
	case 4:
		writel(value, p->base + PCI_DATA);
		break;
	case 2:
		writew(value, p->base + PCI_DATA + (config & 3));
		break;
	case 1:
		writeb(value, p->base + PCI_DATA + (config & 3));
		break;
	default:
		ret = PCIBIOS_BAD_REGISTER_NUMBER;
	}

	return ret;
}