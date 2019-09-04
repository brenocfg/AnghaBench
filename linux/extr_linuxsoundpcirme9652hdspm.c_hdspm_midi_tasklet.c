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
struct hdspm {int midiPorts; TYPE_1__* midi; } ;
struct TYPE_2__ {scalar_t__ pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hdspm_midi_input_read (TYPE_1__*) ; 

__attribute__((used)) static void hdspm_midi_tasklet(unsigned long arg)
{
	struct hdspm *hdspm = (struct hdspm *)arg;
	int i = 0;

	while (i < hdspm->midiPorts) {
		if (hdspm->midi[i].pending)
			snd_hdspm_midi_input_read(&hdspm->midi[i]);

		i++;
	}
}