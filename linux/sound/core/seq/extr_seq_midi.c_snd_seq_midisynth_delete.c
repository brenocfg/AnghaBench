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
struct seq_midisynth {scalar_t__ seq_client; int /*<<< orphan*/  parser; int /*<<< orphan*/  seq_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_event_port_detach (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_seq_midisynth_delete(struct seq_midisynth *msynth)
{
	if (msynth == NULL)
		return;

	if (msynth->seq_client > 0) {
		/* delete port */
		snd_seq_event_port_detach(msynth->seq_client, msynth->seq_port);
	}

	snd_midi_event_free(msynth->parser);
}