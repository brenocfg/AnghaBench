#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned long long offset; } ;
struct snd_tscm {int /*<<< orphan*/ * tx_midi_substreams; TYPE_2__* spec; TYPE_1__ async_handler; } ;
struct snd_rawmidi_substream {int dummy; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;
struct TYPE_4__ {unsigned int midi_capture_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int calculate_message_bytes (int) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static void handle_midi_tx(struct fw_card *card, struct fw_request *request,
			   int tcode, int destination, int source,
			   int generation, unsigned long long offset,
			   void *data, size_t length, void *callback_data)
{
	struct snd_tscm *tscm = callback_data;
	u32 *buf = (u32 *)data;
	unsigned int messages;
	unsigned int i;
	unsigned int port;
	struct snd_rawmidi_substream *substream;
	u8 *b;
	int bytes;

	if (offset != tscm->async_handler.offset)
		goto end;

	messages = length / 8;
	for (i = 0; i < messages; i++) {
		b = (u8 *)(buf + i * 2);

		port = b[0] >> 4;
		/* TODO: support virtual MIDI ports. */
		if (port >= tscm->spec->midi_capture_ports)
			goto end;

		/* Assume the message length. */
		bytes = calculate_message_bytes(b[1]);
		/* On MIDI data or exclusives. */
		if (bytes <= 0) {
			/* Seek the end of exclusives. */
			for (bytes = 1; bytes < 4; bytes++) {
				if (b[bytes] == 0xf7)
					break;
			}
			if (bytes == 4)
				bytes = 3;
		}

		substream = READ_ONCE(tscm->tx_midi_substreams[port]);
		if (substream != NULL)
			snd_rawmidi_receive(substream, b + 1, bytes);
	}
end:
	fw_send_response(card, request, RCODE_COMPLETE);
}