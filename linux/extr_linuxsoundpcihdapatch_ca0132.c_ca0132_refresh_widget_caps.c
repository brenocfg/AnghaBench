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
struct hda_codec {struct ca0132_spec* spec; } ;
struct TYPE_2__ {int num_dacs; } ;
struct ca0132_spec {int num_outputs; int num_inputs; int /*<<< orphan*/ * input_pins; int /*<<< orphan*/ * adcs; int /*<<< orphan*/ * out_pins; int /*<<< orphan*/ * dacs; TYPE_1__ multiout; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  refresh_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_update_widgets (struct hda_codec*) ; 

__attribute__((used)) static void ca0132_refresh_widget_caps(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	int i;

	codec_dbg(codec, "ca0132_refresh_widget_caps.\n");
	snd_hda_codec_update_widgets(codec);

	for (i = 0; i < spec->multiout.num_dacs; i++)
		refresh_amp_caps(codec, spec->dacs[i], HDA_OUTPUT);

	for (i = 0; i < spec->num_outputs; i++)
		refresh_amp_caps(codec, spec->out_pins[i], HDA_OUTPUT);

	for (i = 0; i < spec->num_inputs; i++) {
		refresh_amp_caps(codec, spec->adcs[i], HDA_INPUT);
		refresh_amp_caps(codec, spec->input_pins[i], HDA_INPUT);
	}
}