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
struct TYPE_2__ {void (* update ) (struct hda_codec*) ;int /*<<< orphan*/  old_hook; scalar_t__ led_value; scalar_t__ capture; int /*<<< orphan*/  led_mode; } ;
struct hda_gen_spec {int /*<<< orphan*/  cap_sync_hook; TYPE_1__ micmute_led; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MICMUTE_LED_FOLLOW_MUTE ; 
 int /*<<< orphan*/  micmute_led_mode_ctl ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (struct hda_gen_spec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_micmute_led ; 

int snd_hda_gen_add_micmute_led(struct hda_codec *codec,
				void (*hook)(struct hda_codec *))
{
	struct hda_gen_spec *spec = codec->spec;

	spec->micmute_led.led_mode = MICMUTE_LED_FOLLOW_MUTE;
	spec->micmute_led.capture = 0;
	spec->micmute_led.led_value = 0;
	spec->micmute_led.old_hook = spec->cap_sync_hook;
	spec->micmute_led.update = hook;
	spec->cap_sync_hook = update_micmute_led;
	if (!snd_hda_gen_add_kctl(spec, NULL, &micmute_led_mode_ctl))
		return -ENOMEM;
	return 0;
}