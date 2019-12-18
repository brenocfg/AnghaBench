#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
struct ff_packet {TYPE_7__ base; int /*<<< orphan*/ * clock; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_1__ base; } ;
struct TYPE_12__ {TYPE_2__ flush_packet; } ;
struct ff_decoder {int /*<<< orphan*/  codec; TYPE_4__ packet_queue; scalar_t__ eof; } ;
struct TYPE_11__ {scalar_t__ nb_samples; int /*<<< orphan*/  format; } ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int FF_PACKET_EMPTY ; 
 int FF_PACKET_FAIL ; 
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_7__*) ; 
 int avcodec_decode_audio4 (int /*<<< orphan*/ ,TYPE_3__*,int*,TYPE_7__*) ; 
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_late_packets (struct ff_decoder*,struct ff_packet*) ; 
 int /*<<< orphan*/  handle_reset_packet (struct ff_decoder*,struct ff_packet*) ; 
 int packet_queue_get (TYPE_4__*,struct ff_packet*,int) ; 
 int /*<<< orphan*/  shrink_packet (struct ff_packet*,int) ; 

__attribute__((used)) static int decode_frame(struct ff_decoder *decoder, struct ff_packet *packet,
                        AVFrame *frame, bool *frame_complete)
{
	int packet_length;
	int ret;

	while (true) {
		if (decoder->eof)
			ret = packet_queue_get(&decoder->packet_queue, packet,
			                       0);
		else
			ret = packet_queue_get(&decoder->packet_queue, packet,
			                       1);

		if (ret == FF_PACKET_EMPTY) {
			return 0;
		} else if (ret == FF_PACKET_FAIL) {
			return -1;
		}

		if (packet->base.data ==
		    decoder->packet_queue.flush_packet.base.data) {
			avcodec_flush_buffers(decoder->codec);
			continue;
		}

		// Packet has a new clock (reset packet)
		if (packet->clock != NULL)
			if (!handle_reset_packet(decoder, packet))
				return -1;

		while (packet->base.size > 0) {
			int complete;

			drop_late_packets(decoder, packet);

			packet_length = avcodec_decode_audio4(decoder->codec,
			                                      frame, &complete,
			                                      &packet->base);

			if (packet_length < 0)
				break;

			shrink_packet(packet, packet_length);

			if (complete == 0 || frame->nb_samples <= 0)
				continue;

			*frame_complete = complete != 0;

			return frame->nb_samples *
			       av_get_bytes_per_sample(frame->format);
		}

		if (packet->base.data != NULL)
			av_packet_unref(&packet->base);
	}
}