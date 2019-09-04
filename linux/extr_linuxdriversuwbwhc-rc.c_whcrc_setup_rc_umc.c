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
struct whcrc {int /*<<< orphan*/  rc_len; int /*<<< orphan*/  area; int /*<<< orphan*/ * rc_base; int /*<<< orphan*/  cmd_dma_buf; int /*<<< orphan*/ * cmd_buf; int /*<<< orphan*/ * evt_buf; int /*<<< orphan*/  evt_dma_buf; struct umc_dev* umc_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct umc_dev {int /*<<< orphan*/  irq; struct device dev; TYPE_1__ resource; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct whcrc*) ; 
 int /*<<< orphan*/ * ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct whcrc*) ; 
 int /*<<< orphan*/ * request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  whcrc_irq_cb ; 

__attribute__((used)) static
int whcrc_setup_rc_umc(struct whcrc *whcrc)
{
	int result = 0;
	struct device *dev = &whcrc->umc_dev->dev;
	struct umc_dev *umc_dev = whcrc->umc_dev;

	whcrc->area = umc_dev->resource.start;
	whcrc->rc_len = resource_size(&umc_dev->resource);
	result = -EBUSY;
	if (request_mem_region(whcrc->area, whcrc->rc_len, KBUILD_MODNAME) == NULL) {
		dev_err(dev, "can't request URC region (%zu bytes @ 0x%lx): %d\n",
			whcrc->rc_len, whcrc->area, result);
		goto error_request_region;
	}

	whcrc->rc_base = ioremap_nocache(whcrc->area, whcrc->rc_len);
	if (whcrc->rc_base == NULL) {
		dev_err(dev, "can't ioremap registers (%zu bytes @ 0x%lx): %d\n",
			whcrc->rc_len, whcrc->area, result);
		goto error_ioremap_nocache;
	}

	result = request_irq(umc_dev->irq, whcrc_irq_cb, IRQF_SHARED,
			     KBUILD_MODNAME, whcrc);
	if (result < 0) {
		dev_err(dev, "can't allocate IRQ %d: %d\n",
			umc_dev->irq, result);
		goto error_request_irq;
	}

	result = -ENOMEM;
	whcrc->cmd_buf = dma_alloc_coherent(&umc_dev->dev, PAGE_SIZE,
					    &whcrc->cmd_dma_buf, GFP_KERNEL);
	if (whcrc->cmd_buf == NULL) {
		dev_err(dev, "Can't allocate cmd transfer buffer\n");
		goto error_cmd_buffer;
	}

	whcrc->evt_buf = dma_alloc_coherent(&umc_dev->dev, PAGE_SIZE,
					    &whcrc->evt_dma_buf, GFP_KERNEL);
	if (whcrc->evt_buf == NULL) {
		dev_err(dev, "Can't allocate evt transfer buffer\n");
		goto error_evt_buffer;
	}
	return 0;

error_evt_buffer:
	dma_free_coherent(&umc_dev->dev, PAGE_SIZE, whcrc->cmd_buf,
			  whcrc->cmd_dma_buf);
error_cmd_buffer:
	free_irq(umc_dev->irq, whcrc);
error_request_irq:
	iounmap(whcrc->rc_base);
error_ioremap_nocache:
	release_mem_region(whcrc->area, whcrc->rc_len);
error_request_region:
	return result;
}