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
struct hda_beep {int playing; int /*<<< orphan*/  (* power_hook ) (struct hda_beep*,int) ;int /*<<< orphan*/  nid; struct hda_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_BEEP_CONTROL ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_power_down (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_power_up (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_beep*,int) ; 
 int /*<<< orphan*/  stub2 (struct hda_beep*,int) ; 

__attribute__((used)) static void generate_tone(struct hda_beep *beep, int tone)
{
	struct hda_codec *codec = beep->codec;

	if (tone && !beep->playing) {
		snd_hda_power_up(codec);
		if (beep->power_hook)
			beep->power_hook(beep, true);
		beep->playing = 1;
	}
	snd_hda_codec_write(codec, beep->nid, 0,
			    AC_VERB_SET_BEEP_CONTROL, tone);
	if (!tone && beep->playing) {
		beep->playing = 0;
		if (beep->power_hook)
			beep->power_hook(beep, false);
		snd_hda_power_down(codec);
	}
}