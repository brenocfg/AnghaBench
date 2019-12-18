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
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {unsigned long long mute_bits; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_gen_update_outputs (struct hda_codec*) ; 
 scalar_t__ snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void asus_tx300_automute(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	snd_hda_gen_update_outputs(codec);
	if (snd_hda_jack_detect(codec, 0x1b))
		spec->gen.mute_bits |= (1ULL << 0x14);
}