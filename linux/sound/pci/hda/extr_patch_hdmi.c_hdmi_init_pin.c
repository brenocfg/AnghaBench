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
struct hdmi_spec {scalar_t__ dyn_pin_out; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int AC_WCAP_OUT_AMP ; 
 int AMP_OUT_UNMUTE ; 
 int PIN_OUT ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_init_pin(struct hda_codec *codec, hda_nid_t pin_nid)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_out;

	/* Unmute */
	if (get_wcaps(codec, pin_nid) & AC_WCAP_OUT_AMP)
		snd_hda_codec_write(codec, pin_nid, 0,
				AC_VERB_SET_AMP_GAIN_MUTE, AMP_OUT_UNMUTE);

	if (spec->dyn_pin_out)
		/* Disable pin out until stream is active */
		pin_out = 0;
	else
		/* Enable pin out: some machines with GM965 gets broken output
		 * when the pin is disabled or changed while using with HDMI
		 */
		pin_out = PIN_OUT;

	snd_hda_codec_write(codec, pin_nid, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, pin_out);
}