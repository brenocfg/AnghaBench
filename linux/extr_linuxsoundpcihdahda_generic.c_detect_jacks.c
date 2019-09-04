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
 int AC_PINCTL_IN_EN ; 
 scalar_t__ HDA_JACK_PRESENT ; 
 int snd_hda_codec_get_pin_target (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hda_jack_detect_state (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool detect_jacks(struct hda_codec *codec, int num_pins, hda_nid_t *pins)
{
	int i;
	bool present = false;

	for (i = 0; i < num_pins; i++) {
		hda_nid_t nid = pins[i];
		if (!nid)
			break;
		/* don't detect pins retasked as inputs */
		if (snd_hda_codec_get_pin_target(codec, nid) & AC_PINCTL_IN_EN)
			continue;
		if (snd_hda_jack_detect_state(codec, nid) == HDA_JACK_PRESENT)
			present = true;
	}
	return present;
}