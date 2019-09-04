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
struct TYPE_2__ {scalar_t__ pci_cfg; int /*<<< orphan*/  shim_offset; int /*<<< orphan*/  dsp_dram_offset; int /*<<< orphan*/  dsp_iram_offset; int /*<<< orphan*/  iram_offset; } ;
struct sst_dsp {int id; TYPE_1__ addr; struct device* dma_dev; } ;
struct sst_adsp_memregion {int start; int end; int blocks; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sst_adsp_memregion*) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
#define  SST_DEV_ID_LYNX_POINT 129 
#define  SST_DEV_ID_WILDCAT_POINT 128 
 int /*<<< orphan*/  SST_LPT_DSP_DRAM_OFFSET ; 
 int /*<<< orphan*/  SST_LPT_DSP_IRAM_OFFSET ; 
 int /*<<< orphan*/  SST_LP_IRAM_OFFSET ; 
 int /*<<< orphan*/  SST_LP_SHIM_OFFSET ; 
 int SST_VDRTCL0_DSRAMPGE_SHIFT ; 
 scalar_t__ SST_VDRTCTL0 ; 
 int /*<<< orphan*/  SST_WPT_DSP_DRAM_OFFSET ; 
 int /*<<< orphan*/  SST_WPT_DSP_IRAM_OFFSET ; 
 int /*<<< orphan*/  SST_WPT_IRAM_OFFSET ; 
 int /*<<< orphan*/  SST_WPT_SHIM_OFFSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int hsw_acpi_resource_map (struct sst_dsp*,struct sst_pdata*) ; 
 int hsw_set_dsp_D0 (struct sst_dsp*) ; 
 struct sst_adsp_memregion* lp_region ; 
 int /*<<< orphan*/  sst_hsw_ops ; 
 int /*<<< orphan*/  sst_mem_block_register (struct sst_dsp*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sst_dsp*) ; 
 struct sst_adsp_memregion* wpt_region ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hsw_init(struct sst_dsp *sst, struct sst_pdata *pdata)
{
	const struct sst_adsp_memregion *region;
	struct device *dev;
	int ret = -ENODEV, i, j, region_count;
	u32 offset, size, fw_dump_bit;

	dev = sst->dma_dev;

	switch (sst->id) {
	case SST_DEV_ID_LYNX_POINT:
		region = lp_region;
		region_count = ARRAY_SIZE(lp_region);
		sst->addr.iram_offset = SST_LP_IRAM_OFFSET;
		sst->addr.dsp_iram_offset = SST_LPT_DSP_IRAM_OFFSET;
		sst->addr.dsp_dram_offset = SST_LPT_DSP_DRAM_OFFSET;
		sst->addr.shim_offset = SST_LP_SHIM_OFFSET;
		break;
	case SST_DEV_ID_WILDCAT_POINT:
		region = wpt_region;
		region_count = ARRAY_SIZE(wpt_region);
		sst->addr.iram_offset = SST_WPT_IRAM_OFFSET;
		sst->addr.dsp_iram_offset = SST_WPT_DSP_IRAM_OFFSET;
		sst->addr.dsp_dram_offset = SST_WPT_DSP_DRAM_OFFSET;
		sst->addr.shim_offset = SST_WPT_SHIM_OFFSET;
		break;
	default:
		dev_err(dev, "error: failed to get mem resources\n");
		return ret;
	}

	ret = hsw_acpi_resource_map(sst, pdata);
	if (ret < 0) {
		dev_err(dev, "error: failed to map resources\n");
		return ret;
	}

	/* enable the DSP SHIM */
	ret = hsw_set_dsp_D0(sst);
	if (ret < 0) {
		dev_err(dev, "error: failed to set DSP D0 and reset SHIM\n");
		return ret;
	}

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(31));
	if (ret)
		return ret;


	/* register DSP memory blocks - ideally we should get this from ACPI */
	for (i = 0; i < region_count; i++) {
		offset = region[i].start;
		size = (region[i].end - region[i].start) / region[i].blocks;

		/* register individual memory blocks */
		for (j = 0; j < region[i].blocks; j++) {
			sst_mem_block_register(sst, offset, size,
				region[i].type, &sst_hsw_ops, j, sst);
			offset += size;
		}
	}

	/* always enable the block(DSRAM[0]) used for FW dump */
	fw_dump_bit = 1 << SST_VDRTCL0_DSRAMPGE_SHIFT;
	/* set default power gating control, enable power gating control for all blocks. that is,
	can't be accessed, please enable each block before accessing. */
	writel(0xffffffff & ~fw_dump_bit, sst->addr.pci_cfg + SST_VDRTCTL0);

	return 0;
}