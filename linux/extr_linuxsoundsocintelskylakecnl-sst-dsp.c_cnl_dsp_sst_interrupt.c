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
 int CNL_ADSPIS_IPC ; 
 int /*<<< orphan*/  CNL_ADSP_REG_ADSPIS ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  cnl_ipc_int_disable (struct sst_dsp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

irqreturn_t cnl_dsp_sst_interrupt(int irq, void *dev_id)
{
	struct sst_dsp *ctx = dev_id;
	u32 val;
	irqreturn_t ret = IRQ_NONE;

	spin_lock(&ctx->spinlock);

	val = sst_dsp_shim_read_unlocked(ctx, CNL_ADSP_REG_ADSPIS);
	ctx->intr_status = val;

	if (val == 0xffffffff) {
		spin_unlock(&ctx->spinlock);
		return IRQ_NONE;
	}

	if (val & CNL_ADSPIS_IPC) {
		cnl_ipc_int_disable(ctx);
		ret = IRQ_WAKE_THREAD;
	}

	spin_unlock(&ctx->spinlock);

	return ret;
}