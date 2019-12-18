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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int ae5_headphone_gain_val; scalar_t__ out_enum_val; } ;

/* Variables and functions */
 unsigned int AE5_HEADPHONE_GAIN_MAX ; 
 scalar_t__ HEADPHONE_OUT ; 
 int /*<<< orphan*/  ae5_headphone_gain_set (struct hda_codec*,int) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ae5_headphone_gain_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct ca0132_spec *spec = codec->spec;
	int sel = ucontrol->value.enumerated.item[0];
	unsigned int items = AE5_HEADPHONE_GAIN_MAX;

	if (sel >= items)
		return 0;

	codec_dbg(codec, "ae5_headphone_gain: boost=%d\n",
		    sel);

	spec->ae5_headphone_gain_val = sel;

	if (spec->out_enum_val == HEADPHONE_OUT)
		ae5_headphone_gain_set(codec, spec->ae5_headphone_gain_val);

	return 1;
}