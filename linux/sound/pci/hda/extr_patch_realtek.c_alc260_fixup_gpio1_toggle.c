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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_3__ {int* hp_pins; } ;
struct TYPE_4__ {int detect_hp; int automute_speaker; TYPE_1__ autocfg; int /*<<< orphan*/  automute_hook; } ;
struct alc_spec {TYPE_2__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  alc260_gpio1_automute ; 
 int /*<<< orphan*/  alc_setup_gpio (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_gen_hp_automute ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alc260_fixup_gpio1_toggle(struct hda_codec *codec,
				      const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;
	if (action == HDA_FIXUP_ACT_PROBE) {
		/* although the machine has only one output pin, we need to
		 * toggle GPIO1 according to the jack state
		 */
		spec->gen.automute_hook = alc260_gpio1_automute;
		spec->gen.detect_hp = 1;
		spec->gen.automute_speaker = 1;
		spec->gen.autocfg.hp_pins[0] = 0x0f; /* copy it for automute */
		snd_hda_jack_detect_enable_callback(codec, 0x0f,
						    snd_hda_gen_hp_automute);
		alc_setup_gpio(codec, 0x01);
	}
}