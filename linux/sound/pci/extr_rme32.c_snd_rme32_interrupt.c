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
struct rme32 {int rcreg; scalar_t__ iobase; scalar_t__ playback_substream; scalar_t__ capture_substream; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ RME32_IO_CONFIRM_ACTION_IRQ ; 
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 int RME32_RCR_IRQ ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t snd_rme32_interrupt(int irq, void *dev_id)
{
	struct rme32 *rme32 = (struct rme32 *) dev_id;

	rme32->rcreg = readl(rme32->iobase + RME32_IO_CONTROL_REGISTER);
	if (!(rme32->rcreg & RME32_RCR_IRQ)) {
		return IRQ_NONE;
	} else {
		if (rme32->capture_substream) {
			snd_pcm_period_elapsed(rme32->capture_substream);
		}
		if (rme32->playback_substream) {
			snd_pcm_period_elapsed(rme32->playback_substream);
		}
		writel(0, rme32->iobase + RME32_IO_CONFIRM_ACTION_IRQ);
	}
	return IRQ_HANDLED;
}