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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int out_enum_val; unsigned int* vnode_lswitch; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int NUM_OF_OUTPUTS ; 
 size_t VNID_HP_ASEL ; 
 size_t VNODE_START_NID ; 
 TYPE_3__* alt_out_presets ; 
 int /*<<< orphan*/  ca0132_alt_select_out (struct hda_codec*) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int,int /*<<< orphan*/ ) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ca0132_alt_output_select_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	int sel = ucontrol->value.enumerated.item[0];
	unsigned int items = NUM_OF_OUTPUTS;
	unsigned int auto_jack;

	if (sel >= items)
		return 0;

	codec_dbg(codec, "ca0132_alt_output_select: sel=%d, preset=%s\n",
		    sel, alt_out_presets[sel].name);

	spec->out_enum_val = sel;

	auto_jack = spec->vnode_lswitch[VNID_HP_ASEL - VNODE_START_NID];

	if (!auto_jack)
		ca0132_alt_select_out(codec);

	return 1;
}