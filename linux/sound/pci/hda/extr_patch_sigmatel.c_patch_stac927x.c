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
struct TYPE_3__ {int own_eapd_ctl; int beep_nid; } ;
struct sigmatel_spec {int linear_tone_beep; int have_spdif_mux; int eapd_mask; int gpio_mask; int gpio_dir; int gpio_data; int aloopback_mask; int eapd_switch; int /*<<< orphan*/  volknob_init; scalar_t__ aloopback_shift; int /*<<< orphan*/ * aloopback_ctl; TYPE_1__ gen; int /*<<< orphan*/  spdif_labels; } ;
struct hda_codec {TYPE_2__* bus; int /*<<< orphan*/  proc_widget_hook; struct sigmatel_spec* spec; } ;
struct TYPE_4__ {int needs_damn_long_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ACT_PRE_PROBE ; 
 int /*<<< orphan*/  HDA_FIXUP_ACT_PROBE ; 
 int alloc_stac_spec (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_add_verbs (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pick_fixup (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stac927x_core_init ; 
 int /*<<< orphan*/  stac927x_fixup_tbl ; 
 int /*<<< orphan*/  stac927x_fixups ; 
 int /*<<< orphan*/  stac927x_loopback ; 
 int /*<<< orphan*/  stac927x_models ; 
 int /*<<< orphan*/  stac927x_proc_hook ; 
 int /*<<< orphan*/  stac927x_spdif_labels ; 
 int /*<<< orphan*/  stac_free (struct hda_codec*) ; 
 int stac_parse_auto_config (struct hda_codec*) ; 

__attribute__((used)) static int patch_stac927x(struct hda_codec *codec)
{
	struct sigmatel_spec *spec;
	int err;

	err = alloc_stac_spec(codec);
	if (err < 0)
		return err;

	spec = codec->spec;
	spec->linear_tone_beep = 1;
	spec->gen.own_eapd_ctl = 1;
	spec->have_spdif_mux = 1;
	spec->spdif_labels = stac927x_spdif_labels;

	spec->gen.beep_nid = 0x23; /* digital beep */

	/* GPIO0 High = Enable EAPD */
	spec->eapd_mask = spec->gpio_mask = 0x01;
	spec->gpio_dir = spec->gpio_data = 0x01;

	spec->aloopback_ctl = &stac927x_loopback;
	spec->aloopback_mask = 0x40;
	spec->aloopback_shift = 0;
	spec->eapd_switch = 1;

	snd_hda_pick_fixup(codec, stac927x_models, stac927x_fixup_tbl,
			   stac927x_fixups);
	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PRE_PROBE);

	if (!spec->volknob_init)
		snd_hda_add_verbs(codec, stac927x_core_init);

	err = stac_parse_auto_config(codec);
	if (err < 0) {
		stac_free(codec);
		return err;
	}

	codec->proc_widget_hook = stac927x_proc_hook;

	/*
	 * !!FIXME!!
	 * The STAC927x seem to require fairly long delays for certain
	 * command sequences.  With too short delays (even if the answer
	 * is set to RIRB properly), it results in the silence output
	 * on some hardwares like Dell.
	 *
	 * The below flag enables the longer delay (see get_response
	 * in hda_intel.c).
	 */
	codec->bus->needs_damn_long_delay = 1;

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_PROBE);

	return 0;
}