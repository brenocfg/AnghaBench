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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int /*<<< orphan*/  AC_VERB_SET_PIN_WIDGET_CONTROL ; 
 int AC_WCAP_OUT_AMP ; 
 int /*<<< orphan*/  AMP_OUT_UNMUTE ; 
 int /*<<< orphan*/  PIN_OUT ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simple_playback_init(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin = get_pin(spec, 0);
	hda_nid_t pin = per_pin->pin_nid;

	snd_hda_codec_write(codec, pin, 0,
			    AC_VERB_SET_PIN_WIDGET_CONTROL, PIN_OUT);
	/* some codecs require to unmute the pin */
	if (get_wcaps(codec, pin) & AC_WCAP_OUT_AMP)
		snd_hda_codec_write(codec, pin, 0, AC_VERB_SET_AMP_GAIN_MUTE,
				    AMP_OUT_UNMUTE);
	snd_hda_jack_detect_enable(codec, pin);
	return 0;
}