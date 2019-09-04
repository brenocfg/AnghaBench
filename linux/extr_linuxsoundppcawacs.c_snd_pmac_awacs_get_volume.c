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
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_pmac_awacs_get_volume(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	int reg = kcontrol->private_value & 0xff;
	int lshift = (kcontrol->private_value >> 8) & 0xff;
	int inverted = (kcontrol->private_value >> 16) & 1;
	unsigned long flags;
	int vol[2];

	spin_lock_irqsave(&chip->reg_lock, flags);
	vol[0] = (chip->awacs_reg[reg] >> lshift) & 0xf;
	vol[1] = chip->awacs_reg[reg] & 0xf;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	if (inverted) {
		vol[0] = 0x0f - vol[0];
		vol[1] = 0x0f - vol[1];
	}
	ucontrol->value.integer.value[0] = vol[0];
	ucontrol->value.integer.value[1] = vol[1];
	return 0;
}