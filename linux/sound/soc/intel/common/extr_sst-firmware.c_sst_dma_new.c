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
struct sst_pdata {int resindex_dma_base; int dma_engine; int /*<<< orphan*/  irq; scalar_t__ dma_size; scalar_t__ dma_base; } ;
struct TYPE_2__ {scalar_t__ lpe_base; } ;
struct sst_dsp {int fw_use_dma; int /*<<< orphan*/  dev; struct sst_dma* dma; int /*<<< orphan*/  dma_dev; TYPE_1__ addr; struct sst_pdata* pdata; } ;
struct sst_dma {int /*<<< orphan*/  chip; struct sst_dsp* sst; } ;
struct resource {int /*<<< orphan*/  flags; scalar_t__ end; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  mem ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  SST_DMA_TYPE_DW 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct sst_dma*) ; 
 struct sst_dma* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_probe (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sst_dma_new(struct sst_dsp *sst)
{
	struct sst_pdata *sst_pdata = sst->pdata;
	struct sst_dma *dma;
	struct resource mem;
	int ret = 0;

	if (sst->pdata->resindex_dma_base == -1)
		/* DMA is not used, return and squelsh error messages */
		return 0;

	/* configure the correct platform data for whatever DMA engine
	* is attached to the ADSP IP. */
	switch (sst->pdata->dma_engine) {
	case SST_DMA_TYPE_DW:
		break;
	default:
		dev_err(sst->dev, "error: invalid DMA engine %d\n",
			sst->pdata->dma_engine);
		return -EINVAL;
	}

	dma = devm_kzalloc(sst->dev, sizeof(struct sst_dma), GFP_KERNEL);
	if (!dma)
		return -ENOMEM;

	dma->sst = sst;

	memset(&mem, 0, sizeof(mem));

	mem.start = sst->addr.lpe_base + sst_pdata->dma_base;
	mem.end   = sst->addr.lpe_base + sst_pdata->dma_base + sst_pdata->dma_size - 1;
	mem.flags = IORESOURCE_MEM;

	/* now register DMA engine device */
	dma->chip = dw_probe(sst->dma_dev, &mem, sst_pdata->irq);
	if (IS_ERR(dma->chip)) {
		dev_err(sst->dev, "error: DMA device register failed\n");
		ret = PTR_ERR(dma->chip);
		goto err_dma_dev;
	}

	sst->dma = dma;
	sst->fw_use_dma = true;
	return 0;

err_dma_dev:
	devm_kfree(sst->dev, dma);
	return ret;
}