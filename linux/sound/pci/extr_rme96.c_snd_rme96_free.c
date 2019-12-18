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
struct rme96 {int irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  capture_suspend_buffer; int /*<<< orphan*/  playback_suspend_buffer; scalar_t__ port; int /*<<< orphan*/ * iobase; int /*<<< orphan*/  areg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME96_AR_DAC_EN ; 
 int RME96_IO_ADDITIONAL_REG ; 
 int /*<<< orphan*/  RME96_STOP_BOTH ; 
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rme96_trigger (struct rme96*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snd_rme96_free(void *private_data)
{
	struct rme96 *rme96 = (struct rme96 *)private_data;

	if (!rme96)
	        return;

	if (rme96->irq >= 0) {
		snd_rme96_trigger(rme96, RME96_STOP_BOTH);
		rme96->areg &= ~RME96_AR_DAC_EN;
		writel(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
		free_irq(rme96->irq, (void *)rme96);
		rme96->irq = -1;
	}
	if (rme96->iobase) {
		iounmap(rme96->iobase);
		rme96->iobase = NULL;
	}
	if (rme96->port) {
		pci_release_regions(rme96->pci);
		rme96->port = 0;
	}
#ifdef CONFIG_PM_SLEEP
	vfree(rme96->playback_suspend_buffer);
	vfree(rme96->capture_suspend_buffer);
#endif
	pci_disable_device(rme96->pci);
}