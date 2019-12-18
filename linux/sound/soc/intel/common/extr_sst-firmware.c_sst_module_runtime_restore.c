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
struct sst_module_runtime_context {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  dma_buffer; } ;
struct sst_module_runtime {scalar_t__ persistent_offset; int /*<<< orphan*/  id; struct sst_module* module; struct sst_dsp* dsp; } ;
struct sst_module {int /*<<< orphan*/  persistent_size; } ;
struct TYPE_2__ {scalar_t__ lpe; scalar_t__ lpe_base; } ;
struct sst_dsp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dma_dev; TYPE_1__ addr; int /*<<< orphan*/  dev; scalar_t__ fw_use_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_dma_copyto (struct sst_dsp*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_dsp_dma_get_channel (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_dma_put_channel (struct sst_dsp*) ; 
 int /*<<< orphan*/  sst_memcpy32 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sst_module_runtime_restore(struct sst_module_runtime *runtime,
	struct sst_module_runtime_context *context)
{
	struct sst_dsp *dsp = runtime->dsp;
	struct sst_module *module = runtime->module;
	int ret = 0;

	dev_dbg(dsp->dev, "restoring runtime %d memory at 0x%x size 0x%x\n",
		runtime->id, runtime->persistent_offset,
		module->persistent_size);

	mutex_lock(&dsp->mutex);

	if (!context->buffer) {
		dev_info(dsp->dev, "no context buffer need to restore!\n");
		goto err;
	}

	if (dsp->fw_use_dma) {

		ret = sst_dsp_dma_get_channel(dsp, 0);
		if (ret < 0)
			goto err;

		ret = sst_dsp_dma_copyto(dsp,
			dsp->addr.lpe_base + runtime->persistent_offset,
			context->dma_buffer, module->persistent_size);
		sst_dsp_dma_put_channel(dsp);
		if (ret < 0) {
			dev_err(dsp->dev, "error: module copy failed\n");
			goto err;
		}
	} else
		sst_memcpy32(dsp->addr.lpe + runtime->persistent_offset,
			context->buffer, module->persistent_size);

	dma_free_coherent(dsp->dma_dev, module->persistent_size,
				context->buffer, context->dma_buffer);
	context->buffer = NULL;

err:
	mutex_unlock(&dsp->mutex);
	return ret;
}