#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ff_frame {int dummy; } ;
struct ff_decoder {int abort; int finished; unsigned int packet_queue_size; double timer_next_wake; int previous_pts_diff; int first_frame; int /*<<< orphan*/  packet_queue; int /*<<< orphan*/  refresh_timer; int /*<<< orphan*/  frame_queue; scalar_t__ predicted_pts; scalar_t__ start_pts; scalar_t__ current_pts_time; int /*<<< orphan*/ * stream; TYPE_1__* codec; } ;
struct TYPE_3__ {struct ff_decoder* opaque; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (struct ff_decoder*) ; 
 scalar_t__ av_gettime () ; 
 struct ff_decoder* av_mallocz (int) ; 
 int ff_circular_queue_init (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  ff_decoder_refresh ; 
 int /*<<< orphan*/  ff_timer_free (int /*<<< orphan*/ *) ; 
 int ff_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ff_decoder*) ; 
 int /*<<< orphan*/  packet_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_init (int /*<<< orphan*/ *) ; 

struct ff_decoder *ff_decoder_init(AVCodecContext *codec_context,
                                   AVStream *stream,
                                   unsigned int packet_queue_size,
                                   unsigned int frame_queue_size)
{
	bool success;

	assert(codec_context != NULL);
	assert(stream != NULL);

	struct ff_decoder *decoder = av_mallocz(sizeof(struct ff_decoder));

	if (decoder == NULL)
		goto fail;

	decoder->codec = codec_context;
	decoder->codec->opaque = decoder;
	decoder->stream = stream;
	decoder->abort = false;
	decoder->finished = false;

	decoder->packet_queue_size = packet_queue_size;
	if (!packet_queue_init(&decoder->packet_queue))
		goto fail1;

	decoder->timer_next_wake = (double)av_gettime() / 1000000.0;
	decoder->previous_pts_diff = 40e-3;
	decoder->current_pts_time = av_gettime();
	decoder->start_pts = 0;
	decoder->predicted_pts = 0;
	decoder->first_frame = true;

	success = ff_timer_init(&decoder->refresh_timer, ff_decoder_refresh,
	                        decoder);
	if (!success)
		goto fail2;

	success = ff_circular_queue_init(&decoder->frame_queue,
	                                 sizeof(struct ff_frame),
	                                 frame_queue_size);
	if (!success)
		goto fail3;

	return decoder;

fail3:
	ff_timer_free(&decoder->refresh_timer);
fail2:
	packet_queue_free(&decoder->packet_queue);
fail1:
	av_free(decoder);
fail:
	return NULL;
}