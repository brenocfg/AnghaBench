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
struct hda_codec {struct alc_spec* spec; } ;
struct auto_pin_cfg {int num_inputs; TYPE_1__* inputs; } ;
struct TYPE_4__ {struct auto_pin_cfg autocfg; } ;
struct alc_spec {TYPE_2__ gen; } ;
typedef  int hda_nid_t ;
struct TYPE_3__ {scalar_t__ type; int pin; } ;

/* Variables and functions */
 scalar_t__ AUTO_PIN_MIC ; 
 scalar_t__ INPUT_PIN_ATTR_INT ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int) ; 
 scalar_t__ snd_hda_get_input_pin_attr (unsigned int) ; 

__attribute__((used)) static int find_ext_mic_pin(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;
	struct auto_pin_cfg *cfg = &spec->gen.autocfg;
	hda_nid_t nid;
	unsigned int defcfg;
	int i;

	for (i = 0; i < cfg->num_inputs; i++) {
		if (cfg->inputs[i].type != AUTO_PIN_MIC)
			continue;
		nid = cfg->inputs[i].pin;
		defcfg = snd_hda_codec_get_pincfg(codec, nid);
		if (snd_hda_get_input_pin_attr(defcfg) == INPUT_PIN_ATTR_INT)
			continue;
		return nid;
	}

	return 0;
}