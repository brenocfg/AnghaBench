#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_jack_tbl {int /*<<< orphan*/  pin_sense; scalar_t__ phantom_jack; int /*<<< orphan*/  jack_dirty; int /*<<< orphan*/  nid; } ;
struct TYPE_2__ {int used; struct hda_jack_tbl* list; } ;
struct hda_codec {TYPE_1__ jacktbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_jack_callback (struct hda_codec*,struct hda_jack_tbl*) ; 
 unsigned int get_jack_plug_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_detect_update (struct hda_codec*,struct hda_jack_tbl*) ; 
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 

void snd_hda_jack_poll_all(struct hda_codec *codec)
{
	struct hda_jack_tbl *jack = codec->jacktbl.list;
	int i, changes = 0;

	for (i = 0; i < codec->jacktbl.used; i++, jack++) {
		unsigned int old_sense;
		if (!jack->nid || !jack->jack_dirty || jack->phantom_jack)
			continue;
		old_sense = get_jack_plug_state(jack->pin_sense);
		jack_detect_update(codec, jack);
		if (old_sense == get_jack_plug_state(jack->pin_sense))
			continue;
		changes = 1;
		call_jack_callback(codec, jack);
	}
	if (changes)
		snd_hda_jack_report_sync(codec);
}