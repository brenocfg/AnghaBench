#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_7__ {scalar_t__* value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct hda_codec {struct cs_spec* spec; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dig_out_pins; } ;
struct TYPE_6__ {TYPE_1__ autocfg; } ;
struct cs_spec {int (* spdif_sw_put ) (struct snd_kcontrol*,struct snd_ctl_elem_value*) ;TYPE_2__ gen; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int PIN_OUT ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl_cache (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 struct hda_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int cs4208_spdif_sw_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct hda_codec *codec = snd_kcontrol_chip(kcontrol);
	struct cs_spec *spec = codec->spec;
	hda_nid_t pin = spec->gen.autocfg.dig_out_pins[0];
	int pinctl = ucontrol->value.integer.value[0] ? PIN_OUT : 0;

	snd_hda_set_pin_ctl_cache(codec, pin, pinctl);
	return spec->spdif_sw_put(kcontrol, ucontrol);
}