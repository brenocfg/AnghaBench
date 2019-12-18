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
struct snd_ff {int* rx_midi_error; int /*<<< orphan*/ * rx_midi_work; int /*<<< orphan*/ * rx_bytes; scalar_t__* next_ktime; int /*<<< orphan*/ * rx_midi_substreams; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ rcode_is_permanent_error (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_empty (struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void finish_transmit_midi_msg(struct snd_ff *ff, unsigned int port,
				     int rcode)
{
	struct snd_rawmidi_substream *substream =
				READ_ONCE(ff->rx_midi_substreams[port]);

	if (rcode_is_permanent_error(rcode)) {
		ff->rx_midi_error[port] = true;
		return;
	}

	if (rcode != RCODE_COMPLETE) {
		/* Transfer the message again, immediately. */
		ff->next_ktime[port] = 0;
		schedule_work(&ff->rx_midi_work[port]);
		return;
	}

	snd_rawmidi_transmit_ack(substream, ff->rx_bytes[port]);
	ff->rx_bytes[port] = 0;

	if (!snd_rawmidi_transmit_empty(substream))
		schedule_work(&ff->rx_midi_work[port]);
}