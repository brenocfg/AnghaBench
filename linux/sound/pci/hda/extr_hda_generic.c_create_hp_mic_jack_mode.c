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
struct snd_kcontrol_new {int /*<<< orphan*/  private_value; } ;
struct hda_gen_spec {int hp_mic_jack_modes; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  hp_mic_jack_mode_enum ; 
 struct snd_kcontrol_new* snd_hda_gen_add_kctl (struct hda_gen_spec*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_hp_mic_jack_mode(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	struct snd_kcontrol_new *knew;

	knew = snd_hda_gen_add_kctl(spec, "Headphone Mic Jack Mode",
				    &hp_mic_jack_mode_enum);
	if (!knew)
		return -ENOMEM;
	knew->private_value = pin;
	spec->hp_mic_jack_modes = 1;
	return 0;
}