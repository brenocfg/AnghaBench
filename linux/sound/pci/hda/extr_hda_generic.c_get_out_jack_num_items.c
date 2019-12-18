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
struct hda_gen_spec {scalar_t__ add_jack_modes; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PINCAP_HP_DRV ; 
 unsigned int AC_PINCAP_OUT ; 
 unsigned int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_out_jack_num_items(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	if (spec->add_jack_modes) {
		unsigned int pincap = snd_hda_query_pin_caps(codec, pin);
		if ((pincap & AC_PINCAP_OUT) && (pincap & AC_PINCAP_HP_DRV))
			return 2;
	}
	return 1;
}