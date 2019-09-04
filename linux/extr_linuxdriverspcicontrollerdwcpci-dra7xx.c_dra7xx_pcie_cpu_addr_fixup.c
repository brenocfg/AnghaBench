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
struct dw_pcie {int dummy; } ;

/* Variables and functions */
 int DRA7XX_CPU_TO_BUS_ADDR ; 

__attribute__((used)) static u64 dra7xx_pcie_cpu_addr_fixup(struct dw_pcie *pci, u64 pci_addr)
{
	return pci_addr & DRA7XX_CPU_TO_BUS_ADDR;
}