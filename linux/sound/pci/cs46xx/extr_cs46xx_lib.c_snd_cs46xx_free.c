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
struct snd_cs46xx_region {scalar_t__ resource; int /*<<< orphan*/  remap_addr; } ;
struct TYPE_2__ {struct snd_cs46xx_region* idx; } ;
struct snd_cs46xx {int amplifier; scalar_t__ irq; int /*<<< orphan*/  pci; struct snd_cs46xx* saved_regs; int /*<<< orphan*/  ba1; int /*<<< orphan*/ * modules; int /*<<< orphan*/ * dsp_spos_instance; TYPE_1__ region; int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;int /*<<< orphan*/  (* amplifier_ctrl ) (struct snd_cs46xx*,int) ;} ;

/* Variables and functions */
 int CS46XX_DSP_MODULES ; 
 int EINVAL ; 
 int /*<<< orphan*/  cs46xx_dsp_spos_destroy (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct snd_cs46xx*) ; 
 int /*<<< orphan*/  free_module_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_and_free_resource (scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_cs46xx_hw_stop (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  snd_cs46xx_proc_done (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  snd_cs46xx_remove_gameport (struct snd_cs46xx*) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  stub2 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  stub3 (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cs46xx_free(struct snd_cs46xx *chip)
{
	int idx;

	if (snd_BUG_ON(!chip))
		return -EINVAL;

	if (chip->active_ctrl)
		chip->active_ctrl(chip, 1);

	snd_cs46xx_remove_gameport(chip);

	if (chip->amplifier_ctrl)
		chip->amplifier_ctrl(chip, -chip->amplifier); /* force to off */
	
	snd_cs46xx_proc_done(chip);

	if (chip->region.idx[0].resource)
		snd_cs46xx_hw_stop(chip);

	if (chip->irq >= 0)
		free_irq(chip->irq, chip);

	if (chip->active_ctrl)
		chip->active_ctrl(chip, -chip->amplifier);

	for (idx = 0; idx < 5; idx++) {
		struct snd_cs46xx_region *region = &chip->region.idx[idx];

		iounmap(region->remap_addr);
		release_and_free_resource(region->resource);
	}

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	if (chip->dsp_spos_instance) {
		cs46xx_dsp_spos_destroy(chip);
		chip->dsp_spos_instance = NULL;
	}
	for (idx = 0; idx < CS46XX_DSP_MODULES; idx++)
		free_module_desc(chip->modules[idx]);
#else
	vfree(chip->ba1);
#endif
	
#ifdef CONFIG_PM_SLEEP
	kfree(chip->saved_regs);
#endif

	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}