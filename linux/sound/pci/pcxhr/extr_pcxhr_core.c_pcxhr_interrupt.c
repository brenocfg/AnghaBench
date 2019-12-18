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
struct pcxhr_mgr {int timer_toggle; unsigned int src_it_dsp; TYPE_1__* pci; int /*<<< orphan*/  dsp_time_last; int /*<<< orphan*/  dsp_time_err; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  PCXHR_DSP_TIME_INVALID ; 
 unsigned int PCXHR_FATAL_DSP_ERR ; 
 unsigned int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 unsigned int PCXHR_IRQCS_ACTIVE_PCIDB ; 
 unsigned int PCXHR_IRQ_ASYNC ; 
 unsigned int PCXHR_IRQ_MASK ; 
 unsigned int PCXHR_IRQ_TIMER ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PCXHR_PLX_IRQCS ; 
 int /*<<< orphan*/  PCXHR_PLX_L2PCIDB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

irqreturn_t pcxhr_interrupt(int irq, void *dev_id)
{
	struct pcxhr_mgr *mgr = dev_id;
	unsigned int reg;
	bool wake_thread = false;

	reg = PCXHR_INPL(mgr, PCXHR_PLX_IRQCS);
	if (! (reg & PCXHR_IRQCS_ACTIVE_PCIDB)) {
		/* this device did not cause the interrupt */
		return IRQ_NONE;
	}

	/* clear interrupt */
	reg = PCXHR_INPL(mgr, PCXHR_PLX_L2PCIDB);
	PCXHR_OUTPL(mgr, PCXHR_PLX_L2PCIDB, reg);

	/* timer irq occurred */
	if (reg & PCXHR_IRQ_TIMER) {
		int timer_toggle = reg & PCXHR_IRQ_TIMER;
		if (timer_toggle == mgr->timer_toggle) {
			dev_dbg(&mgr->pci->dev, "ERROR TIMER TOGGLE\n");
			mgr->dsp_time_err++;
		}

		mgr->timer_toggle = timer_toggle;
		mgr->src_it_dsp = reg;
		wake_thread = true;
	}

	/* other irq's handled in the thread */
	if (reg & PCXHR_IRQ_MASK) {
		if (reg & PCXHR_IRQ_ASYNC) {
			/* as we didn't request any async notifications,
			 * some kind of xrun error will probably occurred
			 */
			/* better resynchronize all streams next interrupt : */
			mgr->dsp_time_last = PCXHR_DSP_TIME_INVALID;
		}
		mgr->src_it_dsp = reg;
		wake_thread = true;
	}
#ifdef CONFIG_SND_DEBUG_VERBOSE
	if (reg & PCXHR_FATAL_DSP_ERR)
		dev_dbg(&mgr->pci->dev, "FATAL DSP ERROR : %x\n", reg);
#endif

	return wake_thread ? IRQ_WAKE_THREAD : IRQ_HANDLED;
}