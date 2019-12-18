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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  unsol_tag_front_hp; int /*<<< orphan*/  unsol_tag_amic1; int /*<<< orphan*/  unsol_tag_hp; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNSOL_TAG_DSP ; 
 int /*<<< orphan*/  amic_callback ; 
 int /*<<< orphan*/  ca0132_process_dsp_response ; 
 scalar_t__ ca0132_use_alt_functions (struct ca0132_spec*) ; 
 int /*<<< orphan*/  hp_callback ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca0132_init_unsol(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	snd_hda_jack_detect_enable_callback(codec, spec->unsol_tag_hp, hp_callback);
	snd_hda_jack_detect_enable_callback(codec, spec->unsol_tag_amic1,
					    amic_callback);
	snd_hda_jack_detect_enable_callback(codec, UNSOL_TAG_DSP,
					    ca0132_process_dsp_response);
	/* Front headphone jack detection */
	if (ca0132_use_alt_functions(spec))
		snd_hda_jack_detect_enable_callback(codec,
			spec->unsol_tag_front_hp, hp_callback);
}