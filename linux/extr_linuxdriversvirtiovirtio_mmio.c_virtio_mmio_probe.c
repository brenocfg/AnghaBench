#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_4__ {void* vendor; void* device; } ;
struct TYPE_5__ {TYPE_3__ dev; TYPE_1__ id; int /*<<< orphan*/ * config; } ;
struct virtio_mmio_device {int version; TYPE_2__ vdev; int /*<<< orphan*/ * base; int /*<<< orphan*/  lock; int /*<<< orphan*/  virtqueues; struct platform_device* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VIRTIO_MMIO_DEVICE_ID ; 
 int VIRTIO_MMIO_GUEST_PAGE_SIZE ; 
 int VIRTIO_MMIO_MAGIC_VALUE ; 
 int VIRTIO_MMIO_VENDOR_ID ; 
 int VIRTIO_MMIO_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct virtio_mmio_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct virtio_mmio_device*) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int register_virtio_device (TYPE_2__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_mmio_config_ops ; 
 int /*<<< orphan*/  virtio_mmio_release_dev ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtio_mmio_probe(struct platform_device *pdev)
{
	struct virtio_mmio_device *vm_dev;
	struct resource *mem;
	unsigned long magic;
	int rc;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!mem)
		return -EINVAL;

	if (!devm_request_mem_region(&pdev->dev, mem->start,
			resource_size(mem), pdev->name))
		return -EBUSY;

	vm_dev = devm_kzalloc(&pdev->dev, sizeof(*vm_dev), GFP_KERNEL);
	if (!vm_dev)
		return -ENOMEM;

	vm_dev->vdev.dev.parent = &pdev->dev;
	vm_dev->vdev.dev.release = virtio_mmio_release_dev;
	vm_dev->vdev.config = &virtio_mmio_config_ops;
	vm_dev->pdev = pdev;
	INIT_LIST_HEAD(&vm_dev->virtqueues);
	spin_lock_init(&vm_dev->lock);

	vm_dev->base = devm_ioremap(&pdev->dev, mem->start, resource_size(mem));
	if (vm_dev->base == NULL)
		return -EFAULT;

	/* Check magic value */
	magic = readl(vm_dev->base + VIRTIO_MMIO_MAGIC_VALUE);
	if (magic != ('v' | 'i' << 8 | 'r' << 16 | 't' << 24)) {
		dev_warn(&pdev->dev, "Wrong magic value 0x%08lx!\n", magic);
		return -ENODEV;
	}

	/* Check device version */
	vm_dev->version = readl(vm_dev->base + VIRTIO_MMIO_VERSION);
	if (vm_dev->version < 1 || vm_dev->version > 2) {
		dev_err(&pdev->dev, "Version %ld not supported!\n",
				vm_dev->version);
		return -ENXIO;
	}

	vm_dev->vdev.id.device = readl(vm_dev->base + VIRTIO_MMIO_DEVICE_ID);
	if (vm_dev->vdev.id.device == 0) {
		/*
		 * virtio-mmio device with an ID 0 is a (dummy) placeholder
		 * with no function. End probing now with no error reported.
		 */
		return -ENODEV;
	}
	vm_dev->vdev.id.vendor = readl(vm_dev->base + VIRTIO_MMIO_VENDOR_ID);

	if (vm_dev->version == 1) {
		writel(PAGE_SIZE, vm_dev->base + VIRTIO_MMIO_GUEST_PAGE_SIZE);

		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
		/*
		 * In the legacy case, ensure our coherently-allocated virtio
		 * ring will be at an address expressable as a 32-bit PFN.
		 */
		if (!rc)
			dma_set_coherent_mask(&pdev->dev,
					      DMA_BIT_MASK(32 + PAGE_SHIFT));
	} else {
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	}
	if (rc)
		rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (rc)
		dev_warn(&pdev->dev, "Failed to enable 64-bit or 32-bit DMA.  Trying to continue, but this might not work.\n");

	platform_set_drvdata(pdev, vm_dev);

	rc = register_virtio_device(&vm_dev->vdev);
	if (rc)
		put_device(&vm_dev->vdev.dev);

	return rc;
}