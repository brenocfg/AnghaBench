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
struct hda_codec {struct hda_beep* beep; } ;
struct hda_beep {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  turn_off_beep (struct hda_beep*) ; 

int snd_hda_enable_beep_device(struct hda_codec *codec, int enable)
{
	struct hda_beep *beep = codec->beep;
	if (!beep)
		return 0;
	enable = !!enable;
	if (beep->enabled != enable) {
		beep->enabled = enable;
		if (!enable)
			turn_off_beep(beep);
		return 1;
	}
	return 0;
}