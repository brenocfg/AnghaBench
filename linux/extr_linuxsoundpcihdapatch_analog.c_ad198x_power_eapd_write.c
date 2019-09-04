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
struct hda_codec {int /*<<< orphan*/  inv_eapd; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_PINCAP_EAPD ; 
 int /*<<< orphan*/  AC_VERB_SET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad198x_power_eapd_write(struct hda_codec *codec, hda_nid_t front,
				hda_nid_t hp)
{
	if (snd_hda_query_pin_caps(codec, front) & AC_PINCAP_EAPD)
		snd_hda_codec_write(codec, front, 0, AC_VERB_SET_EAPD_BTLENABLE,
			    !codec->inv_eapd ? 0x00 : 0x02);
	if (snd_hda_query_pin_caps(codec, hp) & AC_PINCAP_EAPD)
		snd_hda_codec_write(codec, hp, 0, AC_VERB_SET_EAPD_BTLENABLE,
			    !codec->inv_eapd ? 0x00 : 0x02);
}