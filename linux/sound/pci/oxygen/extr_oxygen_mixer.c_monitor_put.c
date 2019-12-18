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
struct snd_kcontrol {int private_value; struct oxygen* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_ADC_MONITOR ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int monitor_put(struct snd_kcontrol *ctl,
		       struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u8 bit = ctl->private_value;
	int invert = ctl->private_value & (1 << 8);
	u8 oldreg, newreg;
	int changed;

	spin_lock_irq(&chip->reg_lock);
	oldreg = oxygen_read8(chip, OXYGEN_ADC_MONITOR);
	if ((!!value->value.integer.value[0] ^ !!invert) != 0)
		newreg = oldreg | bit;
	else
		newreg = oldreg & ~bit;
	changed = newreg != oldreg;
	if (changed)
		oxygen_write8(chip, OXYGEN_ADC_MONITOR, newreg);
	spin_unlock_irq(&chip->reg_lock);
	return changed;
}