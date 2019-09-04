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
struct cmipci {scalar_t__ irq; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CH_CAPT ; 
 int /*<<< orphan*/  CM_CH_PLAY ; 
 int /*<<< orphan*/  CM_ENSPDOUT ; 
 int /*<<< orphan*/  CM_FM_EN ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL0 ; 
 int /*<<< orphan*/  CM_REG_FUNCTRL1 ; 
 int /*<<< orphan*/  CM_REG_INT_HLDCLR ; 
 int /*<<< orphan*/  CM_REG_LEGACY_CTRL ; 
 int /*<<< orphan*/  CM_REG_MISC_CTRL ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct cmipci*) ; 
 int /*<<< orphan*/  kfree (struct cmipci*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_ch_reset (struct cmipci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_clear_bit (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_free_gameport (struct cmipci*) ; 
 int /*<<< orphan*/  snd_cmipci_mixer_write (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_cmipci_free(struct cmipci *cm)
{
	if (cm->irq >= 0) {
		snd_cmipci_clear_bit(cm, CM_REG_MISC_CTRL, CM_FM_EN);
		snd_cmipci_clear_bit(cm, CM_REG_LEGACY_CTRL, CM_ENSPDOUT);
		snd_cmipci_write(cm, CM_REG_INT_HLDCLR, 0);  /* disable ints */
		snd_cmipci_ch_reset(cm, CM_CH_PLAY);
		snd_cmipci_ch_reset(cm, CM_CH_CAPT);
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, 0); /* disable channels */
		snd_cmipci_write(cm, CM_REG_FUNCTRL1, 0);

		/* reset mixer */
		snd_cmipci_mixer_write(cm, 0, 0);

		free_irq(cm->irq, cm);
	}

	snd_cmipci_free_gameport(cm);
	pci_release_regions(cm->pci);
	pci_disable_device(cm->pci);
	kfree(cm);
	return 0;
}