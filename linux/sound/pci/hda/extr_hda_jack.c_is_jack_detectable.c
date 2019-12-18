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
struct hda_codec {int /*<<< orphan*/  jackpoll_interval; scalar_t__ no_jack_detect; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_DEFCFG_MISC_NO_PRESENCE ; 
 int AC_PINCAP_PRES_DETECT ; 
 int AC_WCAP_UNSOL_CAP ; 
 int get_defcfg_misc (int /*<<< orphan*/ ) ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_query_pin_caps (struct hda_codec*,int /*<<< orphan*/ ) ; 

bool is_jack_detectable(struct hda_codec *codec, hda_nid_t nid)
{
	if (codec->no_jack_detect)
		return false;
	if (!(snd_hda_query_pin_caps(codec, nid) & AC_PINCAP_PRES_DETECT))
		return false;
	if (get_defcfg_misc(snd_hda_codec_get_pincfg(codec, nid)) &
	     AC_DEFCFG_MISC_NO_PRESENCE)
		return false;
	if (!(get_wcaps(codec, nid) & AC_WCAP_UNSOL_CAP) &&
	    !codec->jackpoll_interval)
		return false;
	return true;
}