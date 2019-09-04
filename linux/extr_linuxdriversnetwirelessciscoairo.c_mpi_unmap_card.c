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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned long AUXMEMSIZE ; 
 unsigned long pci_resource_len (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  release_mem_region (unsigned long,unsigned long) ; 

__attribute__((used)) static void mpi_unmap_card(struct pci_dev *pci)
{
	unsigned long mem_start = pci_resource_start(pci, 1);
	unsigned long mem_len = pci_resource_len(pci, 1);
	unsigned long aux_start = pci_resource_start(pci, 2);
	unsigned long aux_len = AUXMEMSIZE;

	release_mem_region(aux_start, aux_len);
	release_mem_region(mem_start, mem_len);
}