#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {unsigned int led_mode; } ;
struct hda_gen_spec {TYPE_3__ micmute_led; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 unsigned int MICMUTE_LED_FOLLOW_MUTE ; 
 int /*<<< orphan*/  call_micmute_led_update (struct hda_codec*) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int micmute_led_mode_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct hda_gen_spec *spec = codec->spec;
	unsigned int mode;

	mode = ucontrol->value.enumerated.item[0];
	if (mode > MICMUTE_LED_FOLLOW_MUTE)
		mode = MICMUTE_LED_FOLLOW_MUTE;
	if (mode == spec->micmute_led.led_mode)
		return 0;
	spec->micmute_led.led_mode = mode;
	call_micmute_led_update(codec);
	return 1;
}