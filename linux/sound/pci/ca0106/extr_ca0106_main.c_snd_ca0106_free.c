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
struct snd_ca0106 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/ * res_port; TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ca0106_stop_chip (struct snd_ca0106*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_ca0106*) ; 
 int /*<<< orphan*/  kfree (struct snd_ca0106*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_1__*) ; 

__attribute__((used)) static int snd_ca0106_free(struct snd_ca0106 *chip)
{
	if (chip->res_port != NULL) {
		/* avoid access to already used hardware */
		ca0106_stop_chip(chip);
	}
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	// release the data
#if 1
	if (chip->buffer.area)
		snd_dma_free_pages(&chip->buffer);
#endif

	// release the i/o port
	release_and_free_resource(chip->res_port);

	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}