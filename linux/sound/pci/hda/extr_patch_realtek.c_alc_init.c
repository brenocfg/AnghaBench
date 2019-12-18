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
struct TYPE_2__ {int skip_verbs; } ;
struct alc_spec {int /*<<< orphan*/  init_amp; TYPE_1__ gen; int /*<<< orphan*/  (* init_hook ) (struct hda_codec*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_FIXUP_ACT_INIT ; 
 int /*<<< orphan*/  alc_auto_init_amp (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alc_fix_pll (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_pre_init (struct hda_codec*) ; 
 scalar_t__ is_s4_resume (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_apply_fixup (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_apply_verbs (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static int alc_init(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	/* hibernation resume needs the full chip initialization */
	if (is_s4_resume(codec))
		alc_pre_init(codec);

	if (spec->init_hook)
		spec->init_hook(codec);

	spec->gen.skip_verbs = 1; /* applied in below */
	snd_hda_gen_init(codec);
	alc_fix_pll(codec);
	alc_auto_init_amp(codec, spec->init_amp);
	snd_hda_apply_verbs(codec); /* apply verbs here after own init */

	snd_hda_apply_fixup(codec, HDA_FIXUP_ACT_INIT);

	return 0;
}