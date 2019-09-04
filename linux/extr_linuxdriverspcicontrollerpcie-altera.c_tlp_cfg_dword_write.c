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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct altera_pcie {scalar_t__ root_bus_nr; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_PRIMARY_BUS ; 
 scalar_t__ TLP_CFGWR_DW0 (struct altera_pcie*,scalar_t__) ; 
 scalar_t__ TLP_CFG_DW1 (struct altera_pcie*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TLP_CFG_DW2 (scalar_t__,scalar_t__,int) ; 
 int TLP_HDR_SIZE ; 
 int /*<<< orphan*/  TLP_WRITE_TAG ; 
 int tlp_read_packet (struct altera_pcie*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlp_write_packet (struct altera_pcie*,scalar_t__*,scalar_t__,int) ; 

__attribute__((used)) static int tlp_cfg_dword_write(struct altera_pcie *pcie, u8 bus, u32 devfn,
			       int where, u8 byte_en, u32 value)
{
	u32 headers[TLP_HDR_SIZE];
	int ret;

	headers[0] = TLP_CFGWR_DW0(pcie, bus);
	headers[1] = TLP_CFG_DW1(pcie, TLP_WRITE_TAG, byte_en);
	headers[2] = TLP_CFG_DW2(bus, devfn, where);

	/* check alignment to Qword */
	if ((where & 0x7) == 0)
		tlp_write_packet(pcie, headers, value, true);
	else
		tlp_write_packet(pcie, headers, value, false);

	ret = tlp_read_packet(pcie, NULL);
	if (ret != PCIBIOS_SUCCESSFUL)
		return ret;

	/*
	 * Monitor changes to PCI_PRIMARY_BUS register on root port
	 * and update local copy of root bus number accordingly.
	 */
	if ((bus == pcie->root_bus_nr) && (where == PCI_PRIMARY_BUS))
		pcie->root_bus_nr = (u8)(value);

	return PCIBIOS_SUCCESSFUL;
}