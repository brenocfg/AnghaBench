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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCTL2 ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL2_COMP_TIMEOUT ; 
 int pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pqi_set_pcie_completion_timeout(struct pci_dev *pci_dev,
	u16 timeout)
{
	return pcie_capability_clear_and_set_word(pci_dev, PCI_EXP_DEVCTL2,
		PCI_EXP_DEVCTL2_COMP_TIMEOUT, timeout);
}