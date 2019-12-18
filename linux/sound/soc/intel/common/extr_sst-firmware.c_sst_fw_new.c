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
struct sst_fw {int /*<<< orphan*/ * dma_buf; int /*<<< orphan*/  dmable_fw_paddr; int /*<<< orphan*/  size; int /*<<< orphan*/  list; void* private; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dma_dev; scalar_t__ fw_use_dma; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fw_list; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct firmware {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct TYPE_2__ {int (* parse_fw ) (struct sst_fw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sst_fw*) ; 
 struct sst_fw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_dma_get_channel (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_dma_put_channel (struct sst_dsp*) ; 
 int stub1 (struct sst_fw*) ; 

struct sst_fw *sst_fw_new(struct sst_dsp *dsp, 
	const struct firmware *fw, void *private)
{
	struct sst_fw *sst_fw;
	int err;

	if (!dsp->ops->parse_fw)
		return NULL;

	sst_fw = kzalloc(sizeof(*sst_fw), GFP_KERNEL);
	if (sst_fw == NULL)
		return NULL;

	sst_fw->dsp = dsp;
	sst_fw->private = private;
	sst_fw->size = fw->size;

	/* allocate DMA buffer to store FW data */
	sst_fw->dma_buf = dma_alloc_coherent(dsp->dma_dev, sst_fw->size,
				&sst_fw->dmable_fw_paddr, GFP_KERNEL);
	if (!sst_fw->dma_buf) {
		dev_err(dsp->dev, "error: DMA alloc failed\n");
		kfree(sst_fw);
		return NULL;
	}

	/* copy FW data to DMA-able memory */
	memcpy((void *)sst_fw->dma_buf, (void *)fw->data, fw->size);

	if (dsp->fw_use_dma) {
		err = sst_dsp_dma_get_channel(dsp, 0);
		if (err < 0)
			goto chan_err;
	}

	/* call core specific FW paser to load FW data into DSP */
	err = dsp->ops->parse_fw(sst_fw);
	if (err < 0) {
		dev_err(dsp->dev, "error: parse fw failed %d\n", err);
		goto parse_err;
	}

	if (dsp->fw_use_dma)
		sst_dsp_dma_put_channel(dsp);

	mutex_lock(&dsp->mutex);
	list_add(&sst_fw->list, &dsp->fw_list);
	mutex_unlock(&dsp->mutex);

	return sst_fw;

parse_err:
	if (dsp->fw_use_dma)
		sst_dsp_dma_put_channel(dsp);
chan_err:
	dma_free_coherent(dsp->dma_dev, sst_fw->size,
				sst_fw->dma_buf,
				sst_fw->dmable_fw_paddr);
	sst_fw->dma_buf = NULL;
	kfree(sst_fw);
	return NULL;
}