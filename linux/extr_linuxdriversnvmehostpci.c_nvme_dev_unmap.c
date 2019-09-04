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
struct nvme_dev {int /*<<< orphan*/  dev; scalar_t__ bar; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_release_mem_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_dev_unmap(struct nvme_dev *dev)
{
	if (dev->bar)
		iounmap(dev->bar);
	pci_release_mem_regions(to_pci_dev(dev->dev));
}