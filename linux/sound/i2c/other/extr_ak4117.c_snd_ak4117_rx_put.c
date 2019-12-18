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
typedef  int u8 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct ak4117 {int* regmap; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int AK4117_IPS ; 
 size_t AK4117_REG_IO ; 
 int /*<<< orphan*/  reg_write (struct ak4117*,size_t,int) ; 
 struct ak4117* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ak4117_rx_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct ak4117 *chip = snd_kcontrol_chip(kcontrol);
	int change;
	u8 old_val;
	
	spin_lock_irq(&chip->lock);
	old_val = chip->regmap[AK4117_REG_IO];
	change = !!ucontrol->value.integer.value[0] != ((old_val & AK4117_IPS) ? 1 : 0);
	if (change)
		reg_write(chip, AK4117_REG_IO, (old_val & ~AK4117_IPS) | (ucontrol->value.integer.value[0] ? AK4117_IPS : 0));
	spin_unlock_irq(&chip->lock);
	return change;
}