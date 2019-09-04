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
 int /*<<< orphan*/  pci_aer_exit (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_cap_save_buffers (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iov_release (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vpd_release (struct pci_dev*) ; 

__attribute__((used)) static void pci_release_capabilities(struct pci_dev *dev)
{
	pci_aer_exit(dev);
	pci_vpd_release(dev);
	pci_iov_release(dev);
	pci_free_cap_save_buffers(dev);
}