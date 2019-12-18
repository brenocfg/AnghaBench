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
struct auto_pin_cfg_item {int /*<<< orphan*/  is_headphone_mic; int /*<<< orphan*/  is_headset_mic; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
#define  AC_JACK_AUX 134 
#define  AC_JACK_CD 133 
#define  AC_JACK_DIG_OTHER_IN 132 
#define  AC_JACK_HP_OUT 131 
#define  AC_JACK_LINE_IN 130 
#define  AC_JACK_MIC_IN 129 
#define  AC_JACK_SPDIF_IN 128 
 int INPUT_PIN_ATTR_DOCK ; 
 int get_defcfg_device (unsigned int) ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_get_input_pin_attr (unsigned int) ; 

__attribute__((used)) static const char *hda_get_input_pin_label(struct hda_codec *codec,
					   const struct auto_pin_cfg_item *item,
					   hda_nid_t pin, bool check_location)
{
	unsigned int def_conf;
	static const char * const mic_names[] = {
		"Internal Mic", "Dock Mic", "Mic", "Rear Mic", "Front Mic"
	};
	int attr;

	def_conf = snd_hda_codec_get_pincfg(codec, pin);

	switch (get_defcfg_device(def_conf)) {
	case AC_JACK_MIC_IN:
		if (item && item->is_headset_mic)
			return "Headset Mic";
		if (item && item->is_headphone_mic)
			return "Headphone Mic";
		if (!check_location)
			return "Mic";
		attr = snd_hda_get_input_pin_attr(def_conf);
		if (!attr)
			return "None";
		return mic_names[attr - 1];
	case AC_JACK_LINE_IN:
		if (!check_location)
			return "Line";
		attr = snd_hda_get_input_pin_attr(def_conf);
		if (!attr)
			return "None";
		if (attr == INPUT_PIN_ATTR_DOCK)
			return "Dock Line";
		return "Line";
	case AC_JACK_AUX:
		return "Aux";
	case AC_JACK_CD:
		return "CD";
	case AC_JACK_SPDIF_IN:
		return "SPDIF In";
	case AC_JACK_DIG_OTHER_IN:
		return "Digital In";
	case AC_JACK_HP_OUT:
		return "Headphone Mic";
	default:
		return "Misc";
	}
}