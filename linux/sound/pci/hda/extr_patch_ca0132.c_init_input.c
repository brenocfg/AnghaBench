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
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_AMP_GAIN_MUTE ; 
 int AC_WCAP_IN_AMP ; 
 int /*<<< orphan*/  AMP_IN_UNMUTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_AMP_MUTE ; 
 int /*<<< orphan*/  HDA_AMP_VOLMASK ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  PIN_VREF80 ; 
 int get_wcaps (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_codec_amp_stereo (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_set_pin_ctl (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_input(struct hda_codec *codec, hda_nid_t pin, hda_nid_t adc)
{
	if (pin) {
		snd_hda_set_pin_ctl(codec, pin, PIN_VREF80);
		if (get_wcaps(codec, pin) & AC_WCAP_IN_AMP)
			snd_hda_codec_write(codec, pin, 0,
					    AC_VERB_SET_AMP_GAIN_MUTE,
					    AMP_IN_UNMUTE(0));
	}
	if (adc && (get_wcaps(codec, adc) & AC_WCAP_IN_AMP)) {
		snd_hda_codec_write(codec, adc, 0, AC_VERB_SET_AMP_GAIN_MUTE,
				    AMP_IN_UNMUTE(0));

		/* init to 0 dB and unmute. */
		snd_hda_codec_amp_stereo(codec, adc, HDA_INPUT, 0,
					 HDA_AMP_VOLMASK, 0x5a);
		snd_hda_codec_amp_stereo(codec, adc, HDA_INPUT, 0,
					 HDA_AMP_MUTE, 0);
	}
}