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
typedef  int u8 ;
struct TYPE_2__ {int wait_condition; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  wake_status; } ;
struct sst_dsp {TYPE_1__ cl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKL_ADSP_REG_CL_SD_STS ; 
 int /*<<< orphan*/  SKL_CL_DMA_BUF_COMPLETE ; 
 int /*<<< orphan*/  SKL_CL_DMA_ERR ; 
 int SKL_CL_DMA_SD_INT_COMPLETE ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void skl_cldma_process_intr(struct sst_dsp *ctx)
{
	u8 cl_dma_intr_status;

	cl_dma_intr_status =
		sst_dsp_shim_read_unlocked(ctx, SKL_ADSP_REG_CL_SD_STS);

	if (!(cl_dma_intr_status & SKL_CL_DMA_SD_INT_COMPLETE))
		ctx->cl_dev.wake_status = SKL_CL_DMA_ERR;
	else
		ctx->cl_dev.wake_status = SKL_CL_DMA_BUF_COMPLETE;

	ctx->cl_dev.wait_condition = true;
	wake_up(&ctx->cl_dev.wait_queue);
}