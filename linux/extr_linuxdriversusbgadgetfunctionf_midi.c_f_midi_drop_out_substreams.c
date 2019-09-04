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
struct snd_rawmidi_substream {int dummy; } ;
struct gmidi_in_port {scalar_t__ active; struct snd_rawmidi_substream* substream; } ;
struct f_midi {unsigned int in_ports; struct gmidi_in_port* in_ports_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_drop_output (struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void f_midi_drop_out_substreams(struct f_midi *midi)
{
	unsigned int i;

	for (i = 0; i < midi->in_ports; i++) {
		struct gmidi_in_port *port = midi->in_ports_array + i;
		struct snd_rawmidi_substream *substream = port->substream;

		if (port->active && substream)
			snd_rawmidi_drop_output(substream);
	}
}