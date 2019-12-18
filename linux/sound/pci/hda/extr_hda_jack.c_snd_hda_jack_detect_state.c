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
struct hda_jack_tbl {scalar_t__ phantom_jack; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_PINSENSE_PRESENCE ; 
 int HDA_JACK_NOT_PRESENT ; 
 int HDA_JACK_PHANTOM ; 
 int HDA_JACK_PRESENT ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_pin_sense (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hda_jack_detect_state(struct hda_codec *codec, hda_nid_t nid)
{
	struct hda_jack_tbl *jack = snd_hda_jack_tbl_get(codec, nid);
	if (jack && jack->phantom_jack)
		return HDA_JACK_PHANTOM;
	else if (snd_hda_pin_sense(codec, nid) & AC_PINSENSE_PRESENCE)
		return HDA_JACK_PRESENT;
	else
		return HDA_JACK_NOT_PRESENT;
}