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
struct ca0132_spec {int /*<<< orphan*/ * input_pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_AMP_VOLMASK ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int snd_hda_codec_amp_update (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ca0132_mic_boost_set(struct hda_codec *codec, long val)
{
	struct ca0132_spec *spec = codec->spec;
	int ret = 0;

	if (val) /* on */
		ret = snd_hda_codec_amp_update(codec, spec->input_pins[0], 0,
					HDA_INPUT, 0, HDA_AMP_VOLMASK, 3);
	else /* off */
		ret = snd_hda_codec_amp_update(codec, spec->input_pins[0], 0,
					HDA_INPUT, 0, HDA_AMP_VOLMASK, 0);

	return ret;
}