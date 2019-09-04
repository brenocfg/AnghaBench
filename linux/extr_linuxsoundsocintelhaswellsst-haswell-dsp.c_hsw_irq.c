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
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_NONE ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int /*<<< orphan*/  SST_IMRX_BUSY ; 
 int /*<<< orphan*/  SST_IMRX_DONE ; 
 int /*<<< orphan*/  SST_ISRX ; 
 int SST_ISRX_BUSY ; 
 int SST_ISRX_DONE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sst_irq_busy (int,int) ; 
 int /*<<< orphan*/  trace_sst_irq_done (int,int) ; 

__attribute__((used)) static irqreturn_t hsw_irq(int irq, void *context)
{
	struct sst_dsp *sst = (struct sst_dsp *) context;
	u32 isr;
	int ret = IRQ_NONE;

	spin_lock(&sst->spinlock);

	/* Interrupt arrived, check src */
	isr = sst_dsp_shim_read_unlocked(sst, SST_ISRX);
	if (isr & SST_ISRX_DONE) {
		trace_sst_irq_done(isr,
			sst_dsp_shim_read_unlocked(sst, SST_IMRX));

		/* Mask Done interrupt before return */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IMRX,
			SST_IMRX_DONE, SST_IMRX_DONE);
		ret = IRQ_WAKE_THREAD;
	}

	if (isr & SST_ISRX_BUSY) {
		trace_sst_irq_busy(isr,
			sst_dsp_shim_read_unlocked(sst, SST_IMRX));

		/* Mask Busy interrupt before return */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IMRX,
			SST_IMRX_BUSY, SST_IMRX_BUSY);
		ret = IRQ_WAKE_THREAD;
	}

	spin_unlock(&sst->spinlock);
	return ret;
}