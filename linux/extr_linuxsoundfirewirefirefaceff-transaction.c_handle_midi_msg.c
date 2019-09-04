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
typedef  int u8 ;
typedef  int u32 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ff {int /*<<< orphan*/ * tx_midi_substreams; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_COMPLETE ; 
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static void handle_midi_msg(struct fw_card *card, struct fw_request *request,
			    int tcode, int destination, int source,
			    int generation, unsigned long long offset,
			    void *data, size_t length, void *callback_data)
{
	struct snd_ff *ff = callback_data;
	__le32 *buf = data;
	u32 quad;
	u8 byte;
	unsigned int index;
	struct snd_rawmidi_substream *substream;
	int i;

	fw_send_response(card, request, RCODE_COMPLETE);

	for (i = 0; i < length / 4; i++) {
		quad = le32_to_cpu(buf[i]);

		/* Message in first port. */
		/*
		 * This value may represent the index of this unit when the same
		 * units are on the same IEEE 1394 bus. This driver doesn't use
		 * it.
		 */
		index = (quad >> 8) & 0xff;
		if (index > 0) {
			substream = READ_ONCE(ff->tx_midi_substreams[0]);
			if (substream != NULL) {
				byte = quad & 0xff;
				snd_rawmidi_receive(substream, &byte, 1);
			}
		}

		/* Message in second port. */
		index = (quad >> 24) & 0xff;
		if (index > 0) {
			substream = READ_ONCE(ff->tx_midi_substreams[1]);
			if (substream != NULL) {
				byte = (quad >> 16) & 0xff;
				snd_rawmidi_receive(substream, &byte, 1);
			}
		}
	}
}