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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {scalar_t__ mute_led_nid; scalar_t__ cap_mute_led_nid; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  snd_hda_codec_get_pin_target (struct hda_codec*,scalar_t__) ; 
 unsigned int snd_hda_gen_path_power_filter (struct hda_codec*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int led_power_filter(struct hda_codec *codec,
						  hda_nid_t nid,
						  unsigned int power_state)
{
	struct alc_spec *spec = codec->spec;

	if (power_state != AC_PWRST_D3 || nid == 0 ||
	    (nid != spec->mute_led_nid && nid != spec->cap_mute_led_nid))
		return power_state;

	/* Set pin ctl again, it might have just been set to 0 */
	snd_hda_set_pin_ctl(codec, nid,
			    snd_hda_codec_get_pin_target(codec, nid));

	return snd_hda_gen_path_power_filter(codec, nid, power_state);
}