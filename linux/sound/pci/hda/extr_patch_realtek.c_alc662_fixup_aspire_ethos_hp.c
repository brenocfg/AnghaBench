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
struct hda_fixup {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
#define  HDA_FIXUP_ACT_INIT 129 
#define  HDA_FIXUP_ACT_PRE_PROBE 128 
 int /*<<< orphan*/  alc662_aspire_ethos_mute_speakers (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable_callback (struct hda_codec*,int,int /*<<< orphan*/  (*) (struct hda_codec*,int /*<<< orphan*/ *)) ; 

__attribute__((used)) static void alc662_fixup_aspire_ethos_hp(struct hda_codec *codec,
					const struct hda_fixup *fix, int action)
{
    /* Pin 0x1b: shared headphones jack and surround speakers */
	if (!is_jack_detectable(codec, 0x1b))
		return;

	switch (action) {
	case HDA_FIXUP_ACT_PRE_PROBE:
		snd_hda_jack_detect_enable_callback(codec, 0x1b,
				alc662_aspire_ethos_mute_speakers);
		break;
	case HDA_FIXUP_ACT_INIT:
		/* Make sure to start in a correct state, i.e. if
		 * headphones have been plugged in before powering up the system
		 */
		alc662_aspire_ethos_mute_speakers(codec, NULL);
		break;
	}
}