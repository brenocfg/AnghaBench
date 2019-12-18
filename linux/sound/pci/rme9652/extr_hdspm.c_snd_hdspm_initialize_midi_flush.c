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
struct hdspm {int midiPorts; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hdspm_flush_midi_input (struct hdspm*,int) ; 

__attribute__((used)) static inline void snd_hdspm_initialize_midi_flush(struct hdspm * hdspm)
{
	int i;

	for (i = 0; i < hdspm->midiPorts; i++)
		snd_hdspm_flush_midi_input(hdspm, i);
}