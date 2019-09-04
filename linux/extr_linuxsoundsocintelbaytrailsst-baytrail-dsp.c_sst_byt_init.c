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
typedef  int u32 ;
struct sst_pdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  shim_offset; int /*<<< orphan*/  dram_offset; int /*<<< orphan*/  iram_offset; } ;
struct sst_dsp {int id; int /*<<< orphan*/  dma_dev; TYPE_1__ addr; struct device* dev; } ;
struct sst_adsp_memregion {int start; int end; int blocks; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sst_adsp_memregion*) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  SST_BYT_DRAM_OFFSET ; 
 int /*<<< orphan*/  SST_BYT_IRAM_OFFSET ; 
 int /*<<< orphan*/  SST_BYT_SHIM_OFFSET ; 
#define  SST_DEV_ID_BYT 128 
 int /*<<< orphan*/  SST_IMRD ; 
 int /*<<< orphan*/  SST_IMRX ; 
 struct sst_adsp_memregion* byt_region ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_coerce_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_byt_resource_map (struct sst_dsp*,struct sst_pdata*) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits64 (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sst_mem_block_register (struct sst_dsp*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sst_dsp*) ; 

__attribute__((used)) static int sst_byt_init(struct sst_dsp *sst, struct sst_pdata *pdata)
{
	const struct sst_adsp_memregion *region;
	struct device *dev;
	int ret = -ENODEV, i, j, region_count;
	u32 offset, size;

	dev = sst->dev;

	switch (sst->id) {
	case SST_DEV_ID_BYT:
		region = byt_region;
		region_count = ARRAY_SIZE(byt_region);
		sst->addr.iram_offset = SST_BYT_IRAM_OFFSET;
		sst->addr.dram_offset = SST_BYT_DRAM_OFFSET;
		sst->addr.shim_offset = SST_BYT_SHIM_OFFSET;
		break;
	default:
		dev_err(dev, "failed to get mem resources\n");
		return ret;
	}

	ret = sst_byt_resource_map(sst, pdata);
	if (ret < 0) {
		dev_err(dev, "failed to map resources\n");
		return ret;
	}

	ret = dma_coerce_mask_and_coherent(sst->dma_dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	/* enable Interrupt from both sides */
	sst_dsp_shim_update_bits64(sst, SST_IMRX, 0x3, 0x0);
	sst_dsp_shim_update_bits64(sst, SST_IMRD, 0x3, 0x0);

	/* register DSP memory blocks - ideally we should get this from ACPI */
	for (i = 0; i < region_count; i++) {
		offset = region[i].start;
		size = (region[i].end - region[i].start) / region[i].blocks;

		/* register individual memory blocks */
		for (j = 0; j < region[i].blocks; j++) {
			sst_mem_block_register(sst, offset, size,
					       region[i].type, NULL, j, sst);
			offset += size;
		}
	}

	return 0;
}