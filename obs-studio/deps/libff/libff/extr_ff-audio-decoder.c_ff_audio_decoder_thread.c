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
struct ff_packet {int /*<<< orphan*/  base; int /*<<< orphan*/  member_0; } ;
struct ff_decoder {int finished; int /*<<< orphan*/ * clock; int /*<<< orphan*/  abort; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free_packet (int /*<<< orphan*/ *) ; 
 int decode_frame (struct ff_decoder*,struct ff_packet*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ff_clock_release (int /*<<< orphan*/ **) ; 
 double ff_decoder_get_best_effort_pts (struct ff_decoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_frame (struct ff_decoder*,int /*<<< orphan*/ *,double) ; 

void *ff_audio_decoder_thread(void *opaque_audio_decoder)
{
	struct ff_decoder *decoder = opaque_audio_decoder;

	struct ff_packet packet = {0};
	bool frame_complete;
	AVFrame *frame = av_frame_alloc();
	int ret;

	while (!decoder->abort) {
		ret = decode_frame(decoder, &packet, frame, &frame_complete);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			av_free_packet(&packet.base);
			continue;
		}

		// Did we get a audio frame?
		if (frame_complete) {
			// If we don't have a good PTS, try to guess based
			// on last received PTS provided plus prediction
			// This function returns a pts scaled to stream
			// time base
			double best_effort_pts =
			        ff_decoder_get_best_effort_pts(decoder, frame);
			queue_frame(decoder, frame, best_effort_pts);
			av_frame_unref(frame);
		}

		av_free_packet(&packet.base);
	}

	if (decoder->clock != NULL)
		ff_clock_release(&decoder->clock);

	av_frame_free(&frame);

	decoder->finished = true;

	return NULL;
}