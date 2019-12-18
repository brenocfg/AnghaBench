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
struct hda_jack_callback {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {scalar_t__ dc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  olpc_xo_update_mic_boost (struct hda_codec*) ; 
 int /*<<< orphan*/  olpc_xo_update_mic_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_mic_autoswitch (struct hda_codec*,struct hda_jack_callback*) ; 

__attribute__((used)) static void olpc_xo_automic(struct hda_codec *codec,
			    struct hda_jack_callback *jack)
{
	struct conexant_spec *spec = codec->spec;

	/* in DC mode, we don't handle automic */
	if (!spec->dc_enable)
		snd_hda_gen_mic_autoswitch(codec, jack);
	olpc_xo_update_mic_pins(codec);
	if (spec->dc_enable)
		olpc_xo_update_mic_boost(codec);
}