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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct echoaudio {int num_clock_sources; int* clock_source_list; } ;

/* Variables and functions */
 int ECHO_CLOCK_NUMBER ; 
 int detect_input_clocks (struct echoaudio*) ; 
 int num_analog_busses_in (struct echoaudio*) ; 
 int num_analog_busses_out (struct echoaudio*) ; 
 int num_busses_in (struct echoaudio*) ; 
 int num_busses_out (struct echoaudio*) ; 
 int num_pipes_out (struct echoaudio*) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_channels_info_get(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct echoaudio *chip;
	int detected, clocks, bit, src;

	chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.integer.value[0] = num_busses_in(chip);
	ucontrol->value.integer.value[1] = num_analog_busses_in(chip);
	ucontrol->value.integer.value[2] = num_busses_out(chip);
	ucontrol->value.integer.value[3] = num_analog_busses_out(chip);
	ucontrol->value.integer.value[4] = num_pipes_out(chip);

	/* Compute the bitmask of the currently valid input clocks */
	detected = detect_input_clocks(chip);
	clocks = 0;
	src = chip->num_clock_sources - 1;
	for (bit = ECHO_CLOCK_NUMBER - 1; bit >= 0; bit--)
		if (detected & (1 << bit))
			for (; src >= 0; src--)
				if (bit == chip->clock_source_list[src]) {
					clocks |= 1 << src;
					break;
				}
	ucontrol->value.integer.value[5] = clocks;

	return 0;
}