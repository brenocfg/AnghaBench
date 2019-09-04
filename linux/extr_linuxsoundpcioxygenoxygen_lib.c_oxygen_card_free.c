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
struct snd_card {struct oxygen* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct oxygen*) ;} ;
struct oxygen {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  mutex; int /*<<< orphan*/  model_data; TYPE_1__ model; int /*<<< orphan*/  gpio_work; int /*<<< orphan*/  spdif_input_bits_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct oxygen*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxygen_shutdown (struct oxygen*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*) ; 

__attribute__((used)) static void oxygen_card_free(struct snd_card *card)
{
	struct oxygen *chip = card->private_data;

	oxygen_shutdown(chip);
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	flush_work(&chip->spdif_input_bits_work);
	flush_work(&chip->gpio_work);
	chip->model.cleanup(chip);
	kfree(chip->model_data);
	mutex_destroy(&chip->mutex);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
}