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
typedef  int u16 ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {scalar_t__* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int GPIO_CLARO_DIG_COAX ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int claro_dig_source_put(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u16 old_reg, new_reg;
	int changed;

	mutex_lock(&chip->mutex);
	old_reg = oxygen_read16(chip, OXYGEN_GPIO_DATA);
	new_reg = old_reg & ~GPIO_CLARO_DIG_COAX;
	if (value->value.enumerated.item[0])
		new_reg |= GPIO_CLARO_DIG_COAX;
	changed = new_reg != old_reg;
	if (changed)
		oxygen_write16(chip, OXYGEN_GPIO_DATA, new_reg);
	mutex_unlock(&chip->mutex);
	return changed;
}