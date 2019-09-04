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
struct TYPE_2__ {int /*<<< orphan*/ * area; } ;
struct snd_korg1212 {scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_1__ dma_shared; TYPE_1__ dma_rec; TYPE_1__ dma_play; TYPE_1__ dma_dsp; int /*<<< orphan*/ * iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_korg1212*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_korg1212*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_korg1212_DisableCardInterrupts (struct snd_korg1212*) ; 
 int /*<<< orphan*/  snd_korg1212_TurnOffIdleMonitor (struct snd_korg1212*) ; 

__attribute__((used)) static int
snd_korg1212_free(struct snd_korg1212 *korg1212)
{
        snd_korg1212_TurnOffIdleMonitor(korg1212);

        if (korg1212->irq >= 0) {
                snd_korg1212_DisableCardInterrupts(korg1212);
                free_irq(korg1212->irq, korg1212);
                korg1212->irq = -1;
        }
        
        if (korg1212->iobase != NULL) {
                iounmap(korg1212->iobase);
                korg1212->iobase = NULL;
        }
        
	pci_release_regions(korg1212->pci);

        // ----------------------------------------------------
        // free up memory resources used for the DSP download.
        // ----------------------------------------------------
        if (korg1212->dma_dsp.area) {
        	snd_dma_free_pages(&korg1212->dma_dsp);
        	korg1212->dma_dsp.area = NULL;
        }

#ifndef K1212_LARGEALLOC

        // ------------------------------------------------------
        // free up memory resources used for the Play/Rec Buffers
        // ------------------------------------------------------
	if (korg1212->dma_play.area) {
		snd_dma_free_pages(&korg1212->dma_play);
		korg1212->dma_play.area = NULL;
        }

	if (korg1212->dma_rec.area) {
		snd_dma_free_pages(&korg1212->dma_rec);
		korg1212->dma_rec.area = NULL;
        }

#endif

        // ----------------------------------------------------
        // free up memory resources used for the Shared Buffers
        // ----------------------------------------------------
	if (korg1212->dma_shared.area) {
		snd_dma_free_pages(&korg1212->dma_shared);
		korg1212->dma_shared.area = NULL;
        }
        
	pci_disable_device(korg1212->pci);
        kfree(korg1212);
        return 0;
}