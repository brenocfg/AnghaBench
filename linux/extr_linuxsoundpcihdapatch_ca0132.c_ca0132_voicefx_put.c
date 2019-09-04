#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int* item; } ;
struct TYPE_7__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int voicefx_val; } ;
struct TYPE_9__ {int /*<<< orphan*/ * reqs; int /*<<< orphan*/  mid; } ;
struct TYPE_8__ {int /*<<< orphan*/ * vals; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int VOICEFX_MAX_PARAM_COUNT ; 
 TYPE_4__ ca0132_voicefx ; 
 TYPE_3__* ca0132_voicefx_presets ; 
 int /*<<< orphan*/  ca0132_voicefx_set (struct hda_codec*,int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int,int /*<<< orphan*/ ) ; 
 int dspio_set_uint_param (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ca0132_voicefx_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	int i, err = 0;
	int sel = ucontrol->value.enumerated.item[0];

	if (sel >= ARRAY_SIZE(ca0132_voicefx_presets))
		return 0;

	codec_dbg(codec, "ca0132_voicefx_put: sel=%d, preset=%s\n",
		    sel, ca0132_voicefx_presets[sel].name);

	/*
	 * Idx 0 is default.
	 * Default needs to qualify with CrystalVoice state.
	 */
	for (i = 0; i < VOICEFX_MAX_PARAM_COUNT; i++) {
		err = dspio_set_uint_param(codec, ca0132_voicefx.mid,
				ca0132_voicefx.reqs[i],
				ca0132_voicefx_presets[sel].vals[i]);
		if (err < 0)
			break;
	}

	if (err >= 0) {
		spec->voicefx_val = sel;
		/* enable voice fx */
		ca0132_voicefx_set(codec, (sel ? 1 : 0));
	}

	return 1;
}