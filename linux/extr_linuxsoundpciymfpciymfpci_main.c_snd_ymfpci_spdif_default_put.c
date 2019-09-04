#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ymfpci {unsigned int spdif_bits; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * pcm_spdif; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_SPDIFOUTCTRL ; 
 int /*<<< orphan*/  YDSXGR_SPDIFOUTSTATUS ; 
 struct snd_ymfpci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_spdif_default_put(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change;

	val = ((ucontrol->value.iec958.status[0] & 0x3e) << 0) |
	      (ucontrol->value.iec958.status[1] << 8);
	spin_lock_irq(&chip->reg_lock);
	change = chip->spdif_bits != val;
	chip->spdif_bits = val;
	if ((snd_ymfpci_readw(chip, YDSXGR_SPDIFOUTCTRL) & 1) && chip->pcm_spdif == NULL)
		snd_ymfpci_writew(chip, YDSXGR_SPDIFOUTSTATUS, chip->spdif_bits);
	spin_unlock_irq(&chip->reg_lock);
	return change;
}