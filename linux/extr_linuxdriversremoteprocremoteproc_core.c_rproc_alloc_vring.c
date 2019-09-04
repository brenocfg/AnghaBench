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
struct rproc_vring {int notifyid; void* dma; void* va; int /*<<< orphan*/  align; int /*<<< orphan*/  len; } ;
struct rproc_vdev {int rsc_offset; struct rproc_vring* vring; struct rproc* rproc; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct rproc {int max_notifyid; scalar_t__ table_ptr; int /*<<< orphan*/  notifyids; struct device dev; } ;
struct fw_rsc_vdev {TYPE_1__* vring; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int notifyid; void* da; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,void*,void**,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,void*,void*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct rproc_vring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rproc_alloc_vring(struct rproc_vdev *rvdev, int i)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rproc->dev;
	struct rproc_vring *rvring = &rvdev->vring[i];
	struct fw_rsc_vdev *rsc;
	dma_addr_t dma;
	void *va;
	int ret, size, notifyid;

	/* actual size of vring (in bytes) */
	size = PAGE_ALIGN(vring_size(rvring->len, rvring->align));

	/*
	 * Allocate non-cacheable memory for the vring. In the future
	 * this call will also configure the IOMMU for us
	 */
	va = dma_alloc_coherent(dev->parent, size, &dma, GFP_KERNEL);
	if (!va) {
		dev_err(dev->parent, "dma_alloc_coherent failed\n");
		return -EINVAL;
	}

	/*
	 * Assign an rproc-wide unique index for this vring
	 * TODO: assign a notifyid for rvdev updates as well
	 * TODO: support predefined notifyids (via resource table)
	 */
	ret = idr_alloc(&rproc->notifyids, rvring, 0, 0, GFP_KERNEL);
	if (ret < 0) {
		dev_err(dev, "idr_alloc failed: %d\n", ret);
		dma_free_coherent(dev->parent, size, va, dma);
		return ret;
	}
	notifyid = ret;

	/* Potentially bump max_notifyid */
	if (notifyid > rproc->max_notifyid)
		rproc->max_notifyid = notifyid;

	dev_dbg(dev, "vring%d: va %pK dma %pad size 0x%x idr %d\n",
		i, va, &dma, size, notifyid);

	rvring->va = va;
	rvring->dma = dma;
	rvring->notifyid = notifyid;

	/*
	 * Let the rproc know the notifyid and da of this vring.
	 * Not all platforms use dma_alloc_coherent to automatically
	 * set up the iommu. In this case the device address (da) will
	 * hold the physical address and not the device address.
	 */
	rsc = (void *)rproc->table_ptr + rvdev->rsc_offset;
	rsc->vring[i].da = dma;
	rsc->vring[i].notifyid = notifyid;
	return 0;
}