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
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int GPIO_ST_HP_REAR ; 
 int GPIO_XENSE_SPEAKERS ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xense_output_switch_get(struct snd_kcontrol *ctl,
				   struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u16 gpio;

	gpio = oxygen_read16(chip, OXYGEN_GPIO_DATA);
	if (gpio & GPIO_XENSE_SPEAKERS)
		value->value.enumerated.item[0] = 0;
	else if (!(gpio & GPIO_XENSE_SPEAKERS) && (gpio & GPIO_ST_HP_REAR))
		value->value.enumerated.item[0] = 1;
	else
		value->value.enumerated.item[0] = 2;
	return 0;
}