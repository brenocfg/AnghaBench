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
struct snd_ymfpci {int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 struct snd_ymfpci* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned int snd_ymfpci_readl (struct snd_ymfpci*,unsigned int) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ymfpci_put_double(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ymfpci *chip = snd_kcontrol_chip(kcontrol);
	unsigned int reg = kcontrol->private_value;
	unsigned int shift_left = 0, shift_right = 16, mask = 16383;
	int change;
	unsigned int val1, val2, oval;
	
	if (reg < 0x80 || reg >= 0xc0)
		return -EINVAL;
	val1 = ucontrol->value.integer.value[0] & mask;
	val2 = ucontrol->value.integer.value[1] & mask;
	val1 <<= shift_left;
	val2 <<= shift_right;
	spin_lock_irq(&chip->reg_lock);
	oval = snd_ymfpci_readl(chip, reg);
	val1 = (oval & ~((mask << shift_left) | (mask << shift_right))) | val1 | val2;
	change = val1 != oval;
	snd_ymfpci_writel(chip, reg, val1);
	spin_unlock_irq(&chip->reg_lock);
	return change;
}