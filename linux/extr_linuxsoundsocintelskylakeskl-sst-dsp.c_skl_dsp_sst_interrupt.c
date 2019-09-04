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
typedef  int u32 ;
struct sst_dsp {int intr_status; int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int SKL_ADSPIS_CL_DMA ; 
 int SKL_ADSPIS_IPC ; 
 int /*<<< orphan*/  SKL_ADSP_REG_ADSPIS ; 
 int /*<<< orphan*/  skl_cldma_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_ipc_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

irqreturn_t skl_dsp_sst_interrupt(int irq, void *dev_id)
{
	struct sst_dsp *ctx = dev_id;
	u32 val;
	irqreturn_t result = IRQ_NONE;

	spin_lock(&ctx->spinlock);

	val = sst_dsp_shim_read_unlocked(ctx, SKL_ADSP_REG_ADSPIS);
	ctx->intr_status = val;

	if (val == 0xffffffff) {
		spin_unlock(&ctx->spinlock);
		return IRQ_NONE;
	}

	if (val & SKL_ADSPIS_IPC) {
		skl_ipc_int_disable(ctx);
		result = IRQ_WAKE_THREAD;
	}

	if (val & SKL_ADSPIS_CL_DMA) {
		skl_cldma_int_disable(ctx);
		result = IRQ_WAKE_THREAD;
	}

	spin_unlock(&ctx->spinlock);

	return result;
}