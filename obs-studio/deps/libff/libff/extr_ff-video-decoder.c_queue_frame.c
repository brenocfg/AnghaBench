#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ff_frame {double pts; int /*<<< orphan*/  clock; TYPE_2__* frame; } ;
struct ff_decoder {int /*<<< orphan*/  frame_queue; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  clock; TYPE_1__* codec; scalar_t__ abort; } ;
struct TYPE_5__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; scalar_t__ pix_fmt; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 TYPE_2__* av_frame_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_callbacks_frame_initialize (struct ff_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_circular_queue_advance_write (int /*<<< orphan*/ *,struct ff_frame*) ; 
 struct ff_frame* ff_circular_queue_peek_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_circular_queue_wait_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_clock_retain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool queue_frame(struct ff_decoder *decoder, AVFrame *frame,
                        double best_effort_pts)
{
	struct ff_frame *queue_frame;
	bool call_initialize;

	ff_circular_queue_wait_write(&decoder->frame_queue);

	if (decoder->abort) {
		return false;
	}

	queue_frame = ff_circular_queue_peek_write(&decoder->frame_queue);

	// Check if we need to communicate a different format has been received
	// to any callbacks
	AVCodecContext *codec = decoder->codec;
	call_initialize = (queue_frame->frame == NULL ||
	                   queue_frame->frame->width != codec->width ||
	                   queue_frame->frame->height != codec->height ||
	                   queue_frame->frame->format != codec->pix_fmt);

	if (queue_frame->frame != NULL) {
		// This shouldn't happen any more, the frames are freed in
		// ff_decoder_refresh.
		av_frame_free(&queue_frame->frame);
	}

	queue_frame->frame = av_frame_clone(frame);
	queue_frame->clock = ff_clock_retain(decoder->clock);

	if (call_initialize)
		ff_callbacks_frame_initialize(queue_frame, decoder->callbacks);

	queue_frame->pts = best_effort_pts;

	ff_circular_queue_advance_write(&decoder->frame_queue, queue_frame);

	return true;
}