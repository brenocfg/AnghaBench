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
struct echoaudio {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  iores; int /*<<< orphan*/  dsp_registers; int /*<<< orphan*/  commpage_dma_buf; scalar_t__ comm_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_firmware_cache (struct echoaudio*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct echoaudio*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct echoaudio*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rest_in_peace (struct echoaudio*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_echo_free(struct echoaudio *chip)
{
	if (chip->comm_page)
		rest_in_peace(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	if (chip->comm_page)
		snd_dma_free_pages(&chip->commpage_dma_buf);

	iounmap(chip->dsp_registers);
	release_and_free_resource(chip->iores);
	pci_disable_device(chip->pci);

	/* release chip data */
	free_firmware_cache(chip);
	kfree(chip);
	return 0;
}