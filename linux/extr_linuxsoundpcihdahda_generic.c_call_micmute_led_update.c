#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int led_mode; unsigned int led_value; int /*<<< orphan*/  (* update ) (struct hda_codec*) ;int /*<<< orphan*/  capture; } ;
struct hda_gen_spec {TYPE_1__ micmute_led; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
#define  MICMUTE_LED_FOLLOW_CAPTURE 131 
#define  MICMUTE_LED_FOLLOW_MUTE 130 
#define  MICMUTE_LED_OFF 129 
#define  MICMUTE_LED_ON 128 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static void call_micmute_led_update(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	unsigned int val;

	switch (spec->micmute_led.led_mode) {
	case MICMUTE_LED_ON:
		val = 1;
		break;
	case MICMUTE_LED_OFF:
		val = 0;
		break;
	case MICMUTE_LED_FOLLOW_CAPTURE:
		val = !!spec->micmute_led.capture;
		break;
	case MICMUTE_LED_FOLLOW_MUTE:
	default:
		val = !spec->micmute_led.capture;
		break;
	}

	if (val == spec->micmute_led.led_value)
		return;
	spec->micmute_led.led_value = val;
	if (spec->micmute_led.update)
		spec->micmute_led.update(codec);
}