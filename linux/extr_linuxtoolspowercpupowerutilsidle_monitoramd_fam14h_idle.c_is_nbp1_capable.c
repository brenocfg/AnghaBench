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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_NBP1_CAP_OFFSET ; 
 int /*<<< orphan*/  amd_fam14h_pci_dev ; 
 int pci_read_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_nbp1_capable(void)
{
	uint32_t val;
	val = pci_read_long(amd_fam14h_pci_dev, PCI_NBP1_CAP_OFFSET);
	return val & (1 << 31);
}