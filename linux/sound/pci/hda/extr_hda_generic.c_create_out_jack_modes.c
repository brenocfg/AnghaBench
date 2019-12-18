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
struct snd_kcontrol_new {scalar_t__ private_value; } ;
struct hda_gen_spec {scalar_t__ hp_mic_pin; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SNDRV_CTL_ELEM_ID_NAME_MAXLEN ; 
 int /*<<< orphan*/  get_jack_mode_name (struct hda_codec*,scalar_t__,char*,int) ; 
 int get_out_jack_num_items (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  out_jack_mode_enum ; 
 struct snd_kcontrol_new* snd_hda_gen_add_kctl (struct hda_gen_spec*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_out_jack_modes(struct hda_codec *codec, int num_pins,
				 hda_nid_t *pins)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < num_pins; i++) {
		hda_nid_t pin = pins[i];
		if (pin == spec->hp_mic_pin)
			continue;
		if (get_out_jack_num_items(codec, pin) > 1) {
			struct snd_kcontrol_new *knew;
			char name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];
			get_jack_mode_name(codec, pin, name, sizeof(name));
			knew = snd_hda_gen_add_kctl(spec, name,
						    &out_jack_mode_enum);
			if (!knew)
				return -ENOMEM;
			knew->private_value = pin;
		}
	}

	return 0;
}