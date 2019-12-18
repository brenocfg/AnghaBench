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
struct via82xx {scalar_t__ irq; unsigned int num_devs; scalar_t__ chip_type; int /*<<< orphan*/  pci; int /*<<< orphan*/  old_legacy_cfg; int /*<<< orphan*/  old_legacy; int /*<<< orphan*/  mpu_res; int /*<<< orphan*/ * devs; } ;

/* Variables and functions */
 scalar_t__ TYPE_VIA686 ; 
 int /*<<< orphan*/  VIA_FUNC_ENABLE ; 
 int /*<<< orphan*/  VIA_PNP_CONTROL ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct via82xx*) ; 
 int /*<<< orphan*/  kfree (struct via82xx*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via686_free_gameport (struct via82xx*) ; 
 int /*<<< orphan*/  snd_via82xx_channel_reset (struct via82xx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_via82xx_free(struct via82xx *chip)
{
	unsigned int i;

	if (chip->irq < 0)
		goto __end_hw;
	/* disable interrupts */
	for (i = 0; i < chip->num_devs; i++)
		snd_via82xx_channel_reset(chip, &chip->devs[i]);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
 __end_hw:
	release_and_free_resource(chip->mpu_res);
	pci_release_regions(chip->pci);

	if (chip->chip_type == TYPE_VIA686) {
		snd_via686_free_gameport(chip);
		pci_write_config_byte(chip->pci, VIA_FUNC_ENABLE, chip->old_legacy);
		pci_write_config_byte(chip->pci, VIA_PNP_CONTROL, chip->old_legacy_cfg);
	}
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}