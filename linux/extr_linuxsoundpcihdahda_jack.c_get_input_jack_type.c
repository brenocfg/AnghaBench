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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
#define  AC_JACK_DIG_OTHER_OUT 133 
#define  AC_JACK_HP_OUT 132 
#define  AC_JACK_LINE_OUT 131 
#define  AC_JACK_MIC_IN 130 
#define  AC_JACK_SPDIF_OUT 129 
#define  AC_JACK_SPEAKER 128 
 int SND_JACK_AVOUT ; 
 int SND_JACK_HEADPHONE ; 
 int SND_JACK_LINEIN ; 
 int SND_JACK_LINEOUT ; 
 int SND_JACK_MICROPHONE ; 
 int get_defcfg_device (unsigned int) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_input_jack_type(struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int def_conf = snd_hda_codec_get_pincfg(codec, nid);
	switch (get_defcfg_device(def_conf)) {
	case AC_JACK_LINE_OUT:
	case AC_JACK_SPEAKER:
		return SND_JACK_LINEOUT;
	case AC_JACK_HP_OUT:
		return SND_JACK_HEADPHONE;
	case AC_JACK_SPDIF_OUT:
	case AC_JACK_DIG_OTHER_OUT:
		return SND_JACK_AVOUT;
	case AC_JACK_MIC_IN:
		return SND_JACK_MICROPHONE;
	default:
		return SND_JACK_LINEIN;
	}
}