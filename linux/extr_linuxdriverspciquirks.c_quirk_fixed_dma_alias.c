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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_dma_alias_tbl ; 
 int /*<<< orphan*/  pci_add_dma_alias (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static void quirk_fixed_dma_alias(struct pci_dev *dev)
{
	const struct pci_device_id *id;

	id = pci_match_id(fixed_dma_alias_tbl, dev);
	if (id)
		pci_add_dma_alias(dev, id->driver_data);
}