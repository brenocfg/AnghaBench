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
struct sst_fw {int /*<<< orphan*/  dmable_fw_paddr; scalar_t__ dma_buf; int /*<<< orphan*/  size; int /*<<< orphan*/  list; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  dma_dev; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sst_fw*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void sst_fw_free(struct sst_fw *sst_fw)
{
	struct sst_dsp *dsp = sst_fw->dsp;

	mutex_lock(&dsp->mutex);
	list_del(&sst_fw->list);
	mutex_unlock(&dsp->mutex);

	if (sst_fw->dma_buf)
		dma_free_coherent(dsp->dma_dev, sst_fw->size, sst_fw->dma_buf,
			sst_fw->dmable_fw_paddr);
	kfree(sst_fw);
}