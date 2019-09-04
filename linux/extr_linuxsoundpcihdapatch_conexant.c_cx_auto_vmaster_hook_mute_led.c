#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  mute_led_eapd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cx_auto_vmaster_hook_mute_led(void *private_data, int enabled)
{
	struct hda_codec *codec = private_data;
	struct conexant_spec *spec = codec->spec;

	snd_hda_codec_write(codec, spec->mute_led_eapd, 0,
			    AC_VERB_SET_EAPD_BTLENABLE,
			    enabled ? 0x00 : 0x02);
}