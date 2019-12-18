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
struct sst_module_runtime {int persistent_offset; int /*<<< orphan*/  block_list; struct sst_module* module; struct sst_dsp* dsp; } ;
struct sst_module {scalar_t__ persistent_size; int /*<<< orphan*/  block_list; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;
struct sst_block_allocator {scalar_t__ size; int offset; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  ba ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SST_MEM_DRAM ; 
 int block_alloc (struct sst_dsp*,struct sst_block_allocator*,int /*<<< orphan*/ *) ; 
 int block_alloc_fixed (struct sst_dsp*,struct sst_block_allocator*,int /*<<< orphan*/ *) ; 
 int block_list_prepare (struct sst_dsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_list_remove (struct sst_dsp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct sst_block_allocator*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sst_module_runtime_alloc_blocks(struct sst_module_runtime *runtime,
	int offset)
{
	struct sst_dsp *dsp = runtime->dsp;
	struct sst_module *module = runtime->module;
	struct sst_block_allocator ba;
	int ret;

	if (module->persistent_size == 0)
		return 0;

	memset(&ba, 0, sizeof(ba));
	ba.size = module->persistent_size;
	ba.type = SST_MEM_DRAM;

	mutex_lock(&dsp->mutex);

	/* do we need to allocate at a fixed address ? */
	if (offset != 0) {

		ba.offset = offset;

		dev_dbg(dsp->dev, "persistent fixed block request 0x%x bytes type %d offset 0x%x\n",
			ba.size, ba.type, ba.offset);

		/* alloc blocks that includes this section */
		ret = block_alloc_fixed(dsp, &ba, &runtime->block_list);

	} else {
		dev_dbg(dsp->dev, "persistent block request 0x%x bytes type %d\n",
			ba.size, ba.type);

		/* alloc blocks that includes this section */
		ret = block_alloc(dsp, &ba, &runtime->block_list);
	}
	if (ret < 0) {
		dev_err(dsp->dev,
		"error: no free blocks for runtime module size 0x%x\n",
			module->persistent_size);
		mutex_unlock(&dsp->mutex);
		return -ENOMEM;
	}
	runtime->persistent_offset = ba.offset;

	/* prepare DSP blocks for module copy */
	ret = block_list_prepare(dsp, &runtime->block_list);
	if (ret < 0) {
		dev_err(dsp->dev, "error: runtime block prepare failed\n");
		goto err;
	}

	mutex_unlock(&dsp->mutex);
	return ret;

err:
	block_list_remove(dsp, &module->block_list);
	mutex_unlock(&dsp->mutex);
	return ret;
}