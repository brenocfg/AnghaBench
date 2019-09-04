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
struct TYPE_3__ {int capacity; void** slots; } ;
struct ff_frame {int abort; int /*<<< orphan*/  codec; TYPE_1__ frame_queue; int /*<<< orphan*/  packet_queue; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * frame; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  decoder_thread; int /*<<< orphan*/  refresh_timer; } ;
struct ff_decoder {int abort; int /*<<< orphan*/  codec; TYPE_1__ frame_queue; int /*<<< orphan*/  packet_queue; int /*<<< orphan*/ * clock; int /*<<< orphan*/ * frame; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  decoder_thread; int /*<<< orphan*/  refresh_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (struct ff_frame*) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_callbacks_frame_free (struct ff_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_circular_queue_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_circular_queue_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_clock_release (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_timer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 

void ff_decoder_free(struct ff_decoder *decoder)
{
	void *decoder_thread_result;
	int i;

	assert(decoder != NULL);

	decoder->abort = true;

	ff_circular_queue_abort(&decoder->frame_queue);
	packet_queue_abort(&decoder->packet_queue);

	ff_timer_free(&decoder->refresh_timer);

	pthread_join(decoder->decoder_thread, &decoder_thread_result);

	for (i = 0; i < decoder->frame_queue.capacity; i++) {
		void *item = decoder->frame_queue.slots[i];
		struct ff_frame *frame = (struct ff_frame *)item;

		ff_callbacks_frame_free(frame, decoder->callbacks);

		if (frame != NULL) {
			if (frame->frame != NULL)
				av_frame_unref(frame->frame);
			if (frame->clock != NULL)
				ff_clock_release(&frame->clock);
			av_free(frame);
		}
	}

	packet_queue_free(&decoder->packet_queue);
	ff_circular_queue_free(&decoder->frame_queue);

	avcodec_close(decoder->codec);

	av_free(decoder);
}