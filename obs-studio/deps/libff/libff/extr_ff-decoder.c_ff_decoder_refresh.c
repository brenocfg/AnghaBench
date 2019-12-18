#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ff_frame {double pts; int /*<<< orphan*/  frame; int /*<<< orphan*/  clock; } ;
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_9__ {int abort; } ;
struct ff_decoder {double current_pts; long double current_pts_time; double previous_pts; int first_frame; double previous_pts_diff; double timer_next_wake; TYPE_7__ frame_queue; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  natural_sync_clock; TYPE_1__ refresh_timer; int /*<<< orphan*/  finished; int /*<<< orphan*/  eof; scalar_t__ stream; } ;
struct TYPE_10__ {int /*<<< orphan*/  sync_type; } ;
typedef  TYPE_2__ ff_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 long double av_gettime () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_callbacks_frame (int /*<<< orphan*/ ,struct ff_frame*) ; 
 int /*<<< orphan*/  ff_circular_queue_advance_read (TYPE_7__*) ; 
 struct ff_frame* ff_circular_queue_peek_read (TYPE_7__*) ; 
 TYPE_2__* ff_clock_move (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_clock_release (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_clock_start (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ff_decoder_schedule_refresh (struct ff_decoder*,int) ; 
 double get_sync_adjusted_pts_diff (TYPE_2__*,double,double) ; 

void ff_decoder_refresh(void *opaque)
{
	struct ff_decoder *decoder = (struct ff_decoder *)opaque;

	struct ff_frame *frame;

	if (decoder->stream) {
		if (decoder->frame_queue.size == 0) {
			if (!decoder->eof || !decoder->finished) {
				// We expected a frame, but there were none
				// available

				// Schedule another call as soon as possible
				ff_decoder_schedule_refresh(decoder, 1);
			} else {
				ff_callbacks_frame(decoder->callbacks, NULL);
				decoder->refresh_timer.abort = true;
				// no more refreshes, we are at the eof
				av_log(NULL, AV_LOG_INFO,
				       "refresh timer stopping; eof");
				return;
			}
		} else {
			double pts_diff;
			double delay_until_next_wake;
			bool late_first_frame = false;

			frame = ff_circular_queue_peek_read(
			        &decoder->frame_queue);

			// Get frame clock and start it if needed
			ff_clock_t *clock = ff_clock_move(&frame->clock);
			if (!ff_clock_start(clock, decoder->natural_sync_clock,
			                    &decoder->refresh_timer.abort)) {
				ff_clock_release(&clock);

				// Our clock was never started and deleted or
				// aborted

				if (decoder->refresh_timer.abort) {
					av_log(NULL, AV_LOG_INFO,
					       "refresh timer aborted");
					return;
				}

				// Drop this frame? The only way this can happen
				// is if one stream finishes before another and
				// the input is looping or canceled.  Until we
				// get another clock we will unable to continue

				ff_decoder_schedule_refresh(decoder, 100);

				// Drop this frame as we have no way of timing
				// it
				ff_circular_queue_advance_read(
				        &decoder->frame_queue);
				return;
			}

			decoder->current_pts = frame->pts;
			decoder->current_pts_time = av_gettime();

			// the amount of time until we need to display this
			// frame
			pts_diff = frame->pts - decoder->previous_pts;

			// if the first frame is a very large value, we've most
			// likely started mid-stream, and the initial diff
			// should be ignored.
			if (decoder->first_frame) {
				late_first_frame = pts_diff >= 1.0;
				decoder->first_frame = false;
			}

			if (pts_diff <= 0 || late_first_frame) {
				// if diff is invalid, use previous
				pts_diff = decoder->previous_pts_diff;
			}

			// save for next time
			decoder->previous_pts_diff = pts_diff;
			decoder->previous_pts = frame->pts;

			// if not synced against natural clock
			if (clock->sync_type != decoder->natural_sync_clock) {
				pts_diff = get_sync_adjusted_pts_diff(
				        clock, frame->pts, pts_diff);
			}

			decoder->timer_next_wake += pts_diff;

			// compute the amount of time until next refresh
			delay_until_next_wake = decoder->timer_next_wake -
			                        (av_gettime() / 1000000.0L);
			if (delay_until_next_wake < 0.010L) {
				delay_until_next_wake = 0.010L;
			}

			if (delay_until_next_wake > pts_diff)
				delay_until_next_wake = pts_diff;

			ff_clock_release(&clock);
			ff_callbacks_frame(decoder->callbacks, frame);

			ff_decoder_schedule_refresh(
			        decoder,
			        (int)(delay_until_next_wake * 1000 + 0.5L));

			av_frame_free(&frame->frame);

			ff_circular_queue_advance_read(&decoder->frame_queue);
		}
	} else {
		ff_decoder_schedule_refresh(decoder, 100);
	}
}