#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct obs_source_frame {scalar_t__ timestamp; } ;
struct TYPE_7__ {int num; struct obs_source_frame** array; } ;
struct TYPE_6__ {scalar_t__ last_sys_timestamp; scalar_t__ last_frame_ts; TYPE_5__ async_frames; scalar_t__ async_unbuffered; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ MAX_TS_VAR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  da_erase (TYPE_5__,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_out_of_bounds (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  remove_async_frame (TYPE_1__*,struct obs_source_frame*) ; 

__attribute__((used)) static bool ready_async_frame(obs_source_t *source, uint64_t sys_time)
{
	struct obs_source_frame *next_frame = source->async_frames.array[0];
	struct obs_source_frame *frame = NULL;
	uint64_t sys_offset = sys_time - source->last_sys_timestamp;
	uint64_t frame_time = next_frame->timestamp;
	uint64_t frame_offset = 0;

	if (source->async_unbuffered) {
		while (source->async_frames.num > 1) {
			da_erase(source->async_frames, 0);
			remove_async_frame(source, next_frame);
			next_frame = source->async_frames.array[0];
		}

		source->last_frame_ts = next_frame->timestamp;
		return true;
	}

#if DEBUG_ASYNC_FRAMES
	blog(LOG_DEBUG,
	     "source->last_frame_ts: %llu, frame_time: %llu, "
	     "sys_offset: %llu, frame_offset: %llu, "
	     "number of frames: %lu",
	     source->last_frame_ts, frame_time, sys_offset,
	     frame_time - source->last_frame_ts,
	     (unsigned long)source->async_frames.num);
#endif

	/* account for timestamp invalidation */
	if (frame_out_of_bounds(source, frame_time)) {
#if DEBUG_ASYNC_FRAMES
		blog(LOG_DEBUG, "timing jump");
#endif
		source->last_frame_ts = next_frame->timestamp;
		return true;
	} else {
		frame_offset = frame_time - source->last_frame_ts;
		source->last_frame_ts += sys_offset;
	}

	while (source->last_frame_ts > next_frame->timestamp) {

		/* this tries to reduce the needless frame duplication, also
		 * helps smooth out async rendering to frame boundaries.  In
		 * other words, tries to keep the framerate as smooth as
		 * possible */
		if ((source->last_frame_ts - next_frame->timestamp) < 2000000)
			break;

		if (frame)
			da_erase(source->async_frames, 0);

#if DEBUG_ASYNC_FRAMES
		blog(LOG_DEBUG,
		     "new frame, "
		     "source->last_frame_ts: %llu, "
		     "next_frame->timestamp: %llu",
		     source->last_frame_ts, next_frame->timestamp);
#endif

		remove_async_frame(source, frame);

		if (source->async_frames.num == 1)
			return true;

		frame = next_frame;
		next_frame = source->async_frames.array[1];

		/* more timestamp checking and compensating */
		if ((next_frame->timestamp - frame_time) > MAX_TS_VAR) {
#if DEBUG_ASYNC_FRAMES
			blog(LOG_DEBUG, "timing jump");
#endif
			source->last_frame_ts =
				next_frame->timestamp - frame_offset;
		}

		frame_time = next_frame->timestamp;
		frame_offset = frame_time - source->last_frame_ts;
	}

#if DEBUG_ASYNC_FRAMES
	if (!frame)
		blog(LOG_DEBUG, "no frame!");
#endif

	return frame != NULL;
}