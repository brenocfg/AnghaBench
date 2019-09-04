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
typedef  int u64 ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  SST_BYT_IMRX_REQUEST ; 
 int /*<<< orphan*/  SST_BYT_IPCX_DONE ; 
 int SST_BYT_ISRX_REQUEST ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int /*<<< orphan*/  SST_IPCX ; 
 int /*<<< orphan*/  SST_ISRX ; 
 int SST_ISRX_DONE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sst_dsp_shim_read64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sst_byt_irq(int irq, void *context)
{
	struct sst_dsp *sst = (struct sst_dsp *) context;
	u64 isrx;
	irqreturn_t ret = IRQ_NONE;

	spin_lock(&sst->spinlock);

	isrx = sst_dsp_shim_read64_unlocked(sst, SST_ISRX);
	if (isrx & SST_ISRX_DONE) {
		/* ADSP has processed the message request from IA */
		sst_dsp_shim_update_bits64_unlocked(sst, SST_IPCX,
						    SST_BYT_IPCX_DONE, 0);
		ret = IRQ_WAKE_THREAD;
	}
	if (isrx & SST_BYT_ISRX_REQUEST) {
		/* mask message request from ADSP and do processing later */
		sst_dsp_shim_update_bits64_unlocked(sst, SST_IMRX,
						    SST_BYT_IMRX_REQUEST,
						    SST_BYT_IMRX_REQUEST);
		ret = IRQ_WAKE_THREAD;
	}

	spin_unlock(&sst->spinlock);

	return ret;
}