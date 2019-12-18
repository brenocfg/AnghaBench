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
struct snd_pmac {int* awacs_reg; int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int MASK_GAINLINE ; 
 int MASK_MIC_BOOST ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_pmac_awacs_write_reg (struct snd_pmac*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_pmac_screamer_mic_boost_put(struct snd_kcontrol *kcontrol,
					   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	int changed = 0;
	int val0, val6;
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	val0 = chip->awacs_reg[0] & ~MASK_GAINLINE;
	val6 = chip->awacs_reg[6] & ~MASK_MIC_BOOST;
	if (ucontrol->value.integer.value[0] & 1)
		val0 |= MASK_GAINLINE;
	if (ucontrol->value.integer.value[0] & 2)
		val6 |= MASK_MIC_BOOST;
	if (val0 != chip->awacs_reg[0]) {
		snd_pmac_awacs_write_reg(chip, 0, val0);
		changed = 1;
	}
	if (val6 != chip->awacs_reg[6]) {
		snd_pmac_awacs_write_reg(chip, 6, val6);
		changed = 1;
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return changed;
}