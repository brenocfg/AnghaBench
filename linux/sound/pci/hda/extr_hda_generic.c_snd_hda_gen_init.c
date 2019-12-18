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
struct TYPE_4__ {scalar_t__ hook; scalar_t__ sw_kctl; } ;
struct hda_gen_spec {TYPE_2__ vmaster_mute; int /*<<< orphan*/  skip_verbs; int /*<<< orphan*/  (* init_hook ) (struct hda_codec*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;
struct hda_codec {TYPE_1__ core; struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_unsol_on_unused_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  hda_call_check_power_status (struct hda_codec*,int) ; 
 int /*<<< orphan*/  init_aamix_paths (struct hda_codec*) ; 
 int /*<<< orphan*/  init_analog_input (struct hda_codec*) ; 
 int /*<<< orphan*/  init_digital (struct hda_codec*) ; 
 int /*<<< orphan*/  init_extra_out (struct hda_codec*) ; 
 int /*<<< orphan*/  init_input_src (struct hda_codec*) ; 
 int /*<<< orphan*/  init_multi_io (struct hda_codec*) ; 
 int /*<<< orphan*/  init_multi_out (struct hda_codec*) ; 
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_verbs (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sync_vmaster_hook (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 
 int /*<<< orphan*/  sync_all_pin_power_ctls (struct hda_codec*) ; 
 int /*<<< orphan*/  update_automute_all (struct hda_codec*) ; 

int snd_hda_gen_init(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;

	if (spec->init_hook)
		spec->init_hook(codec);

	if (!spec->skip_verbs)
		snd_hda_apply_verbs(codec);

	init_multi_out(codec);
	init_extra_out(codec);
	init_multi_io(codec);
	init_aamix_paths(codec);
	init_analog_input(codec);
	init_input_src(codec);
	init_digital(codec);

	clear_unsol_on_unused_pins(codec);

	sync_all_pin_power_ctls(codec);

	/* call init functions of standard auto-mute helpers */
	update_automute_all(codec);

	regcache_sync(codec->core.regmap);

	if (spec->vmaster_mute.sw_kctl && spec->vmaster_mute.hook)
		snd_hda_sync_vmaster_hook(&spec->vmaster_mute);

	hda_call_check_power_status(codec, 0x01);
	return 0;
}