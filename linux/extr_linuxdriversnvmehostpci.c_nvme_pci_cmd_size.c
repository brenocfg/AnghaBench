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
struct nvme_iod {int dummy; } ;
struct nvme_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_INT_BYTES (struct nvme_dev*) ; 
 int /*<<< orphan*/  NVME_INT_PAGES ; 
 unsigned int nvme_pci_iod_alloc_size (struct nvme_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int nvme_pci_cmd_size(struct nvme_dev *dev, bool use_sgl)
{
	unsigned int alloc_size = nvme_pci_iod_alloc_size(dev,
				    NVME_INT_BYTES(dev), NVME_INT_PAGES,
				    use_sgl);

	return sizeof(struct nvme_iod) + alloc_size;
}