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
struct rproc_mem_entry {int len; int /*<<< orphan*/  node; int /*<<< orphan*/  da; void* dma; void* va; } ;
struct device {struct device* parent; } ;
struct rproc {int /*<<< orphan*/  carveouts; int /*<<< orphan*/  mappings; scalar_t__ domain; struct device dev; } ;
struct fw_rsc_carveout {int len; int /*<<< orphan*/  da; void* pa; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; scalar_t__ reserved; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*,void**,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dma_alloc_coherent (struct device*,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,void*) ; 
 int iommu_map (scalar_t__,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rproc_mem_entry*) ; 
 struct rproc_mem_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rproc_handle_carveout(struct rproc *rproc,
				 struct fw_rsc_carveout *rsc,
				 int offset, int avail)
{
	struct rproc_mem_entry *carveout, *mapping;
	struct device *dev = &rproc->dev;
	dma_addr_t dma;
	void *va;
	int ret;

	if (sizeof(*rsc) > avail) {
		dev_err(dev, "carveout rsc is truncated\n");
		return -EINVAL;
	}

	/* make sure reserved bytes are zeroes */
	if (rsc->reserved) {
		dev_err(dev, "carveout rsc has non zero reserved bytes\n");
		return -EINVAL;
	}

	dev_dbg(dev, "carveout rsc: name: %s, da 0x%x, pa 0x%x, len 0x%x, flags 0x%x\n",
		rsc->name, rsc->da, rsc->pa, rsc->len, rsc->flags);

	carveout = kzalloc(sizeof(*carveout), GFP_KERNEL);
	if (!carveout)
		return -ENOMEM;

	va = dma_alloc_coherent(dev->parent, rsc->len, &dma, GFP_KERNEL);
	if (!va) {
		dev_err(dev->parent,
			"failed to allocate dma memory: len 0x%x\n", rsc->len);
		ret = -ENOMEM;
		goto free_carv;
	}

	dev_dbg(dev, "carveout va %pK, dma %pad, len 0x%x\n",
		va, &dma, rsc->len);

	/*
	 * Ok, this is non-standard.
	 *
	 * Sometimes we can't rely on the generic iommu-based DMA API
	 * to dynamically allocate the device address and then set the IOMMU
	 * tables accordingly, because some remote processors might
	 * _require_ us to use hard coded device addresses that their
	 * firmware was compiled with.
	 *
	 * In this case, we must use the IOMMU API directly and map
	 * the memory to the device address as expected by the remote
	 * processor.
	 *
	 * Obviously such remote processor devices should not be configured
	 * to use the iommu-based DMA API: we expect 'dma' to contain the
	 * physical address in this case.
	 */
	if (rproc->domain) {
		mapping = kzalloc(sizeof(*mapping), GFP_KERNEL);
		if (!mapping) {
			ret = -ENOMEM;
			goto dma_free;
		}

		ret = iommu_map(rproc->domain, rsc->da, dma, rsc->len,
				rsc->flags);
		if (ret) {
			dev_err(dev, "iommu_map failed: %d\n", ret);
			goto free_mapping;
		}

		/*
		 * We'll need this info later when we'll want to unmap
		 * everything (e.g. on shutdown).
		 *
		 * We can't trust the remote processor not to change the
		 * resource table, so we must maintain this info independently.
		 */
		mapping->da = rsc->da;
		mapping->len = rsc->len;
		list_add_tail(&mapping->node, &rproc->mappings);

		dev_dbg(dev, "carveout mapped 0x%x to %pad\n",
			rsc->da, &dma);
	}

	/*
	 * Some remote processors might need to know the pa
	 * even though they are behind an IOMMU. E.g., OMAP4's
	 * remote M3 processor needs this so it can control
	 * on-chip hardware accelerators that are not behind
	 * the IOMMU, and therefor must know the pa.
	 *
	 * Generally we don't want to expose physical addresses
	 * if we don't have to (remote processors are generally
	 * _not_ trusted), so we might want to do this only for
	 * remote processor that _must_ have this (e.g. OMAP4's
	 * dual M3 subsystem).
	 *
	 * Non-IOMMU processors might also want to have this info.
	 * In this case, the device address and the physical address
	 * are the same.
	 */
	rsc->pa = dma;

	carveout->va = va;
	carveout->len = rsc->len;
	carveout->dma = dma;
	carveout->da = rsc->da;

	list_add_tail(&carveout->node, &rproc->carveouts);

	return 0;

free_mapping:
	kfree(mapping);
dma_free:
	dma_free_coherent(dev->parent, rsc->len, va, dma);
free_carv:
	kfree(carveout);
	return ret;
}