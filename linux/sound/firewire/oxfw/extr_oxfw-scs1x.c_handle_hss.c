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
struct snd_rawmidi_substream {int dummy; } ;
struct TYPE_2__ {unsigned long long offset; } ;
struct fw_scs1x {int /*<<< orphan*/  input; TYPE_1__ hss_handler; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int TCODE_WRITE_BLOCK_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 int /*<<< orphan*/  midi_input_packet (struct fw_scs1x*,struct snd_rawmidi_substream*,void*,size_t) ; 

__attribute__((used)) static void handle_hss(struct fw_card *card, struct fw_request *request,
		       int tcode, int destination, int source, int generation,
		       unsigned long long offset, void *data, size_t length,
		       void *callback_data)
{
	struct fw_scs1x *scs = callback_data;
	struct snd_rawmidi_substream *stream;
	int rcode;

	if (offset != scs->hss_handler.offset) {
		rcode = RCODE_ADDRESS_ERROR;
		goto end;
	}
	if (tcode != TCODE_WRITE_QUADLET_REQUEST &&
	    tcode != TCODE_WRITE_BLOCK_REQUEST) {
		rcode = RCODE_TYPE_ERROR;
		goto end;
	}

	if (length >= 1) {
		stream = READ_ONCE(scs->input);
		if (stream)
			midi_input_packet(scs, stream, data, length);
	}

	rcode = RCODE_COMPLETE;
end:
	fw_send_response(card, request, rcode);
}