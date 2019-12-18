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
struct es1968 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  tea; scalar_t__ io_port; scalar_t__ input_dev; int /*<<< orphan*/  hwvol_work; } ;

/* Variables and functions */
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct es1968*) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct es1968*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1968_free_gameport (struct es1968*) ; 
 int /*<<< orphan*/  snd_tea575x_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_es1968_free(struct es1968 *chip)
{
	cancel_work_sync(&chip->hwvol_work);
#ifdef CONFIG_SND_ES1968_INPUT
	if (chip->input_dev)
		input_unregister_device(chip->input_dev);
#endif

	if (chip->io_port) {
		if (chip->irq >= 0)
			synchronize_irq(chip->irq);
		outw(1, chip->io_port + 0x04); /* clear WP interrupts */
		outw(0, chip->io_port + ESM_PORT_HOST_IRQ); /* disable IRQ */
	}

#ifdef CONFIG_SND_ES1968_RADIO
	snd_tea575x_exit(&chip->tea);
	v4l2_device_unregister(&chip->v4l2_dev);
#endif

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	snd_es1968_free_gameport(chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}