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
struct snd_sof_dev {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_DSP_BAR ; 
 int IRQ_NONE ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  SHIM_ISRX ; 
 int SHIM_ISRX_BUSY ; 
 int SHIM_ISRX_DONE ; 
 int snd_sof_dsp_read64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t byt_irq_handler(int irq, void *context)
{
	struct snd_sof_dev *sdev = context;
	u64 isr;
	int ret = IRQ_NONE;

	/* Interrupt arrived, check src */
	isr = snd_sof_dsp_read64(sdev, BYT_DSP_BAR, SHIM_ISRX);
	if (isr & (SHIM_ISRX_DONE | SHIM_ISRX_BUSY))
		ret = IRQ_WAKE_THREAD;

	return ret;
}