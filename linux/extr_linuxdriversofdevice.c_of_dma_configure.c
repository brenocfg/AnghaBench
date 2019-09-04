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
struct iommu_ops {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int* dma_mask; int coherent_dma_mask; unsigned long dma_pfn_offset; int bus_dma_mask; } ;

/* Variables and functions */
 int DMA_BIT_MASK (scalar_t__) ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct iommu_ops const*) ; 
 unsigned long PFN_DOWN (int) ; 
 int PTR_ERR (struct iommu_ops const*) ; 
 int /*<<< orphan*/  arch_setup_dma_ops (struct device*,int,int,struct iommu_ops const*,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 scalar_t__ ilog2 (int) ; 
 int max (int,int) ; 
 int of_dma_get_range (struct device_node*,int*,int*,int*) ; 
 int of_dma_is_coherent (struct device_node*) ; 
 struct iommu_ops* of_iommu_configure (struct device*,struct device_node*) ; 

int of_dma_configure(struct device *dev, struct device_node *np, bool force_dma)
{
	u64 dma_addr, paddr, size = 0;
	int ret;
	bool coherent;
	unsigned long offset;
	const struct iommu_ops *iommu;
	u64 mask;

	ret = of_dma_get_range(np, &dma_addr, &paddr, &size);
	if (ret < 0) {
		/*
		 * For legacy reasons, we have to assume some devices need
		 * DMA configuration regardless of whether "dma-ranges" is
		 * correctly specified or not.
		 */
		if (!force_dma)
			return ret == -ENODEV ? 0 : ret;

		dma_addr = offset = 0;
	} else {
		offset = PFN_DOWN(paddr - dma_addr);

		/*
		 * Add a work around to treat the size as mask + 1 in case
		 * it is defined in DT as a mask.
		 */
		if (size & 1) {
			dev_warn(dev, "Invalid size 0x%llx for dma-range\n",
				 size);
			size = size + 1;
		}

		if (!size) {
			dev_err(dev, "Adjusted size 0x%llx invalid\n", size);
			return -EINVAL;
		}
		dev_dbg(dev, "dma_pfn_offset(%#08lx)\n", offset);
	}

	/*
	 * If @dev is expected to be DMA-capable then the bus code that created
	 * it should have initialised its dma_mask pointer by this point. For
	 * now, we'll continue the legacy behaviour of coercing it to the
	 * coherent mask if not, but we'll no longer do so quietly.
	 */
	if (!dev->dma_mask) {
		dev_warn(dev, "DMA mask not set\n");
		dev->dma_mask = &dev->coherent_dma_mask;
	}

	if (!size && dev->coherent_dma_mask)
		size = max(dev->coherent_dma_mask, dev->coherent_dma_mask + 1);
	else if (!size)
		size = 1ULL << 32;

	dev->dma_pfn_offset = offset;

	/*
	 * Limit coherent and dma mask based on size and default mask
	 * set by the driver.
	 */
	mask = DMA_BIT_MASK(ilog2(dma_addr + size - 1) + 1);
	dev->coherent_dma_mask &= mask;
	*dev->dma_mask &= mask;
	/* ...but only set bus mask if we found valid dma-ranges earlier */
	if (!ret)
		dev->bus_dma_mask = mask;

	coherent = of_dma_is_coherent(np);
	dev_dbg(dev, "device is%sdma coherent\n",
		coherent ? " " : " not ");

	iommu = of_iommu_configure(dev, np);
	if (IS_ERR(iommu) && PTR_ERR(iommu) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	dev_dbg(dev, "device is%sbehind an iommu\n",
		iommu ? " " : " not ");

	arch_setup_dma_ops(dev, dma_addr, size, iommu, coherent);

	return 0;
}