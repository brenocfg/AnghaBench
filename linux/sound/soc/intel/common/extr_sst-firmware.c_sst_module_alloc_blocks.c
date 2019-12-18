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
struct sst_module {int /*<<< orphan*/  block_list; int /*<<< orphan*/  size; int /*<<< orphan*/  data; scalar_t__ offset; scalar_t__ data_offset; int /*<<< orphan*/  type; struct sst_fw* sst_fw; struct sst_dsp* dsp; } ;
struct sst_fw {scalar_t__ dmable_fw_paddr; } ;
struct TYPE_2__ {scalar_t__ lpe; scalar_t__ lpe_base; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; TYPE_1__ addr; int /*<<< orphan*/  dev; scalar_t__ fw_use_dma; } ;
struct sst_block_allocator {int /*<<< orphan*/  type; scalar_t__ offset; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  ba ;

/* Variables and functions */
 int ENOMEM ; 
 int block_alloc_fixed (struct sst_dsp*,struct sst_block_allocator*,int /*<<< orphan*/ *) ; 
 int block_list_prepare (struct sst_dsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_list_remove (struct sst_dsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct sst_block_allocator*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_dma_copyto (struct sst_dsp*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_memcpy32 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sst_module_alloc_blocks(struct sst_module *module)
{
	struct sst_dsp *dsp = module->dsp;
	struct sst_fw *sst_fw = module->sst_fw;
	struct sst_block_allocator ba;
	int ret;

	memset(&ba, 0, sizeof(ba));
	ba.size = module->size;
	ba.type = module->type;
	ba.offset = module->offset;

	dev_dbg(dsp->dev, "block request 0x%x bytes at offset 0x%x type %d\n",
		ba.size, ba.offset, ba.type);

	mutex_lock(&dsp->mutex);

	/* alloc blocks that includes this section */
	ret = block_alloc_fixed(dsp, &ba, &module->block_list);
	if (ret < 0) {
		dev_err(dsp->dev,
			"error: no free blocks for section at offset 0x%x size 0x%x\n",
			module->offset, module->size);
		mutex_unlock(&dsp->mutex);
		return -ENOMEM;
	}

	/* prepare DSP blocks for module copy */
	ret = block_list_prepare(dsp, &module->block_list);
	if (ret < 0) {
		dev_err(dsp->dev, "error: fw module prepare failed\n");
		goto err;
	}

	/* copy partial module data to blocks */
	if (dsp->fw_use_dma) {
		ret = sst_dsp_dma_copyto(dsp,
			dsp->addr.lpe_base + module->offset,
			sst_fw->dmable_fw_paddr + module->data_offset,
			module->size);
		if (ret < 0) {
			dev_err(dsp->dev, "error: module copy failed\n");
			goto err;
		}
	} else
		sst_memcpy32(dsp->addr.lpe + module->offset, module->data,
			module->size);

	mutex_unlock(&dsp->mutex);
	return ret;

err:
	block_list_remove(dsp, &module->block_list);
	mutex_unlock(&dsp->mutex);
	return ret;
}