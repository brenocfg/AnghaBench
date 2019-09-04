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
struct snd_azf3328 {scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_azf3328*) ; 
 int /*<<< orphan*/  kfree (struct snd_azf3328*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_gameport_free (struct snd_azf3328*) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_reset (struct snd_azf3328*) ; 
 int /*<<< orphan*/  snd_azf3328_timer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_azf3328_free(struct snd_azf3328 *chip)
{
	if (chip->irq < 0)
		goto __end_hw;

	snd_azf3328_mixer_reset(chip);

	snd_azf3328_timer_stop(chip->timer);
	snd_azf3328_gameport_free(chip);

__end_hw:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kfree(chip);
	return 0;
}