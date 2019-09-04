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
struct xonar_pcm179x {int hp_active; } ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int GPIO_ST_HP ; 
 int GPIO_ST_HP_REAR ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_pcm1796_volume (struct oxygen*) ; 

__attribute__((used)) static int st_output_switch_put(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_pcm179x *data = chip->model_data;
	u16 gpio_old, gpio;

	mutex_lock(&chip->mutex);
	gpio_old = oxygen_read16(chip, OXYGEN_GPIO_DATA);
	gpio = gpio_old;
	switch (value->value.enumerated.item[0]) {
	case 0:
		gpio &= ~(GPIO_ST_HP | GPIO_ST_HP_REAR);
		break;
	case 1:
		gpio |= GPIO_ST_HP | GPIO_ST_HP_REAR;
		break;
	case 2:
		gpio = (gpio | GPIO_ST_HP) & ~GPIO_ST_HP_REAR;
		break;
	}
	oxygen_write16(chip, OXYGEN_GPIO_DATA, gpio);
	data->hp_active = gpio & GPIO_ST_HP;
	update_pcm1796_volume(chip);
	mutex_unlock(&chip->mutex);
	return gpio != gpio_old;
}