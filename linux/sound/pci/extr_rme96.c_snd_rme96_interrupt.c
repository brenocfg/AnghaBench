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
struct rme96 {int rcreg; scalar_t__ iobase; int /*<<< orphan*/  capture_substream; int /*<<< orphan*/  playback_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ RME96_IO_CONFIRM_PLAY_IRQ ; 
 scalar_t__ RME96_IO_CONFIRM_REC_IRQ ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int RME96_RCR_IRQ ; 
 int RME96_RCR_IRQ_2 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t
snd_rme96_interrupt(int irq,
		    void *dev_id)
{
	struct rme96 *rme96 = (struct rme96 *)dev_id;

	rme96->rcreg = readl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
	/* fastpath out, to ease interrupt sharing */
	if (!((rme96->rcreg & RME96_RCR_IRQ) ||
	      (rme96->rcreg & RME96_RCR_IRQ_2)))
	{
		return IRQ_NONE;
	}
	
	if (rme96->rcreg & RME96_RCR_IRQ) {
		/* playback */
                snd_pcm_period_elapsed(rme96->playback_substream);
		writel(0, rme96->iobase + RME96_IO_CONFIRM_PLAY_IRQ);
	}
	if (rme96->rcreg & RME96_RCR_IRQ_2) {
		/* capture */
		snd_pcm_period_elapsed(rme96->capture_substream);		
		writel(0, rme96->iobase + RME96_IO_CONFIRM_REC_IRQ);
	}
	return IRQ_HANDLED;
}