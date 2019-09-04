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
struct hda_codec {int dummy; } ;
struct auto_pin_cfg {int /*<<< orphan*/  hp_outs; int /*<<< orphan*/  hp_pins; int /*<<< orphan*/  speaker_outs; int /*<<< orphan*/  speaker_pins; int /*<<< orphan*/  line_outs; int /*<<< orphan*/  line_out_pins; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int INPUT_PIN_ATTR_INT ; 
 char* check_output_pfx (struct hda_codec*,int /*<<< orphan*/ ) ; 
 char* check_output_sfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int get_hp_label_index (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_get_input_pin_attr (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int fill_audio_out_name(struct hda_codec *codec, hda_nid_t nid,
			       const struct auto_pin_cfg *cfg,
			       const char *name, char *label, int maxlen,
			       int *indexp)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	int attr = snd_hda_get_input_pin_attr(def_conf);
	const char *pfx, *sfx = "";

	/* handle as a speaker if it's a fixed line-out */
	if (!strcmp(name, "Line Out") && attr == INPUT_PIN_ATTR_INT)
		name = "Speaker";
	pfx = check_output_pfx(codec, nid);

	if (cfg) {
		/* try to give a unique suffix if needed */
		sfx = check_output_sfx(nid, cfg->line_out_pins, cfg->line_outs,
				       indexp);
		if (!sfx)
			sfx = check_output_sfx(nid, cfg->speaker_pins, cfg->speaker_outs,
					       indexp);
		if (!sfx) {
			/* don't add channel suffix for Headphone controls */
			int idx = get_hp_label_index(codec, nid, cfg->hp_pins,
						     cfg->hp_outs);
			if (idx >= 0 && indexp)
				*indexp = idx;
			sfx = "";
		}
	}
	snprintf(label, maxlen, "%s%s%s", pfx, name, sfx);
	return 1;
}