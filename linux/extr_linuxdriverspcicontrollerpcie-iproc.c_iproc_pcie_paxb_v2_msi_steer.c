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
typedef  int u64 ;
struct of_pci_range {int size; int pci_addr; int cpu_addr; } ;
struct iproc_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  range ;

/* Variables and functions */
 int /*<<< orphan*/  IPROC_PCIE_IB_MAP_IO ; 
 int SZ_32K ; 
 int iproc_pcie_setup_ib (struct iproc_pcie*,struct of_pci_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct of_pci_range*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iproc_pcie_paxb_v2_msi_steer(struct iproc_pcie *pcie, u64 msi_addr)
{
	int ret;
	struct of_pci_range range;

	memset(&range, 0, sizeof(range));
	range.size = SZ_32K;
	range.pci_addr = range.cpu_addr = msi_addr & ~(range.size - 1);

	ret = iproc_pcie_setup_ib(pcie, &range, IPROC_PCIE_IB_MAP_IO);
	return ret;
}