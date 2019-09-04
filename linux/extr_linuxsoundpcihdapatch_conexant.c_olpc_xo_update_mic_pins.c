#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nid_path {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct TYPE_4__ {int** input_paths; size_t* cur_mux; } ;
struct conexant_spec {size_t dc_input_bias; struct nid_path* dc_mode_path; scalar_t__ recording; int /*<<< orphan*/  dc_enable; TYPE_1__ gen; } ;
struct TYPE_6__ {TYPE_2__* items; } ;
struct TYPE_5__ {int index; } ;

/* Variables and functions */
 int PIN_IN ; 
 TYPE_3__ olpc_xo_dc_bias ; 
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int,int) ; 
 int snd_hda_codec_get_pin_target (struct hda_codec*,int) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int) ; 
 int /*<<< orphan*/  update_mic_pin (struct hda_codec*,int,int) ; 

__attribute__((used)) static void olpc_xo_update_mic_pins(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	int cur_input, val;
	struct nid_path *path;

	cur_input = spec->gen.input_paths[0][spec->gen.cur_mux[0]];

	/* Set up mic pins for port-B, C and F dynamically as the recording
	 * LED is turned on/off by these pin controls
	 */
	if (!spec->dc_enable) {
		/* disable DC bias path and pin for port F */
		update_mic_pin(codec, 0x1e, 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, false, false);

		/* update port B (ext mic) and C (int mic) */
		/* OLPC defers mic widget control until when capture is
		 * started because the microphone LED comes on as soon as
		 * these settings are put in place. if we did this before
		 * recording, it would give the false indication that
		 * recording is happening when it is not.
		 */
		update_mic_pin(codec, 0x1a, spec->recording ?
			       snd_hda_codec_get_pin_target(codec, 0x1a) : 0);
		update_mic_pin(codec, 0x1b, spec->recording ?
			       snd_hda_codec_get_pin_target(codec, 0x1b) : 0);
		/* enable normal mic path */
		path = snd_hda_get_path_from_idx(codec, cur_input);
		if (path)
			snd_hda_activate_path(codec, path, true, false);
	} else {
		/* disable normal mic path */
		path = snd_hda_get_path_from_idx(codec, cur_input);
		if (path)
			snd_hda_activate_path(codec, path, false, false);

		/* Even though port F is the DC input, the bias is controlled
		 * on port B.  We also leave that port as an active input (but
		 * unselected) in DC mode just in case that is necessary to
		 * make the bias setting take effect.
		 */
		if (spec->recording)
			val = olpc_xo_dc_bias.items[spec->dc_input_bias].index;
		else
			val = 0;
		update_mic_pin(codec, 0x1a, val);
		update_mic_pin(codec, 0x1b, 0);
		/* enable DC bias path and pin */
		update_mic_pin(codec, 0x1e, spec->recording ? PIN_IN : 0);
		snd_hda_activate_path(codec, spec->dc_mode_path, true, false);
	}
}