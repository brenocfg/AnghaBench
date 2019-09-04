#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct brcmf_pciedev_info {TYPE_1__* pdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  brcmf_pcie_write_tcm32 (struct brcmf_pciedev_info*,scalar_t__,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void *
brcmf_pcie_init_dmabuffer_for_device(struct brcmf_pciedev_info *devinfo,
				     u32 size, u32 tcm_dma_phys_addr,
				     dma_addr_t *dma_handle)
{
	void *ring;
	u64 address;

	ring = dma_alloc_coherent(&devinfo->pdev->dev, size, dma_handle,
				  GFP_KERNEL);
	if (!ring)
		return NULL;

	address = (u64)*dma_handle;
	brcmf_pcie_write_tcm32(devinfo, tcm_dma_phys_addr,
			       address & 0xffffffff);
	brcmf_pcie_write_tcm32(devinfo, tcm_dma_phys_addr + 4, address >> 32);

	memset(ring, 0, size);

	return (ring);
}