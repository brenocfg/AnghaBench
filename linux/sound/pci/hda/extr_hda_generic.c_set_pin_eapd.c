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
struct hda_gen_spec {scalar_t__ keep_eapd_on; scalar_t__ own_eapd_ctl; } ;
struct hda_codec {scalar_t__ inv_eapd; struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_PINCAP_EAPD ; 
 int /*<<< orphan*/  AC_VERB_SET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_pin_eapd(struct hda_codec *codec, hda_nid_t pin, bool enable)
{
	struct hda_gen_spec *spec = codec->spec;
	if (spec->own_eapd_ctl ||
	    !(snd_hda_query_pin_caps(codec, pin) & AC_PINCAP_EAPD))
		return;
	if (spec->keep_eapd_on && !enable)
		return;
	if (codec->inv_eapd)
		enable = !enable;
	snd_hda_codec_write_cache(codec, pin, 0,
				   AC_VERB_SET_EAPD_BTLENABLE,
				   enable ? 0x02 : 0x00);
}