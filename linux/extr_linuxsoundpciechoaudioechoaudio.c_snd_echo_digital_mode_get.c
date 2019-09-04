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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct echoaudio {int digital_mode; int num_digital_modes; int* digital_mode_list; } ;

/* Variables and functions */
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_digital_mode_get(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int i, mode;

	chip = snd_kcontrol_chip(kcontrol);
	mode = chip->digital_mode;
	for (i = chip->num_digital_modes - 1; i >= 0; i--)
		if (mode == chip->digital_mode_list[i]) {
			ucontrol->value.enumerated.item[0] = i;
			break;
		}
	return 0;
}