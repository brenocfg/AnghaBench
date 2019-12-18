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
struct snd_m3 {int num_substreams; scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  assp_minisrc_image; int /*<<< orphan*/  assp_kernel_image; scalar_t__ iobase; int /*<<< orphan*/  suspend_mem; struct snd_m3* substreams; int /*<<< orphan*/  reg_lock; scalar_t__ substream; scalar_t__ running; scalar_t__ input_dev; int /*<<< orphan*/  hwvol_work; } ;
struct m3_dma {int num_substreams; scalar_t__ irq; int /*<<< orphan*/  pci; int /*<<< orphan*/  assp_minisrc_image; int /*<<< orphan*/  assp_kernel_image; scalar_t__ iobase; int /*<<< orphan*/  suspend_mem; struct m3_dma* substreams; int /*<<< orphan*/  reg_lock; scalar_t__ substream; scalar_t__ running; scalar_t__ input_dev; int /*<<< orphan*/  hwvol_work; } ;

/* Variables and functions */
 scalar_t__ HOST_INT_CTRL ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_m3*) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct snd_m3*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_pcm_stop (struct snd_m3*,struct snd_m3*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_m3_free(struct snd_m3 *chip)
{
	struct m3_dma *s;
	int i;

	cancel_work_sync(&chip->hwvol_work);
#ifdef CONFIG_SND_MAESTRO3_INPUT
	if (chip->input_dev)
		input_unregister_device(chip->input_dev);
#endif

	if (chip->substreams) {
		spin_lock_irq(&chip->reg_lock);
		for (i = 0; i < chip->num_substreams; i++) {
			s = &chip->substreams[i];
			/* check surviving pcms; this should not happen though.. */
			if (s->substream && s->running)
				snd_m3_pcm_stop(chip, s, s->substream);
		}
		spin_unlock_irq(&chip->reg_lock);
		kfree(chip->substreams);
	}
	if (chip->iobase) {
		outw(0, chip->iobase + HOST_INT_CTRL); /* disable ints */
	}

#ifdef CONFIG_PM_SLEEP
	vfree(chip->suspend_mem);
#endif

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	if (chip->iobase)
		pci_release_regions(chip->pci);

	release_firmware(chip->assp_kernel_image);
	release_firmware(chip->assp_minisrc_image);

	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}