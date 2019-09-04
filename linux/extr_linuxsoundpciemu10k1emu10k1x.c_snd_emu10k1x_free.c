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
struct TYPE_2__ {scalar_t__ area; } ;
struct emu10k1x {scalar_t__ irq; int /*<<< orphan*/  pci; TYPE_1__ dma_buffer; int /*<<< orphan*/  res_port; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ HCFG ; 
 int /*<<< orphan*/  HCFG_LOCKSOUNDCACHE ; 
 scalar_t__ INTE ; 
 int /*<<< orphan*/  TRIGGER_CHANNEL ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct emu10k1x*) ; 
 int /*<<< orphan*/  kfree (struct emu10k1x*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu10k1x_free(struct emu10k1x *chip)
{
	snd_emu10k1x_ptr_write(chip, TRIGGER_CHANNEL, 0, 0);
	// disable interrupts
	outl(0, chip->port + INTE);
	// disable audio
	outl(HCFG_LOCKSOUNDCACHE, chip->port + HCFG);

	/* release the irq */
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	// release the i/o port
	release_and_free_resource(chip->res_port);

	// release the DMA
	if (chip->dma_buffer.area) {
		snd_dma_free_pages(&chip->dma_buffer);
	}

	pci_disable_device(chip->pci);

	// release the data
	kfree(chip);
	return 0;
}