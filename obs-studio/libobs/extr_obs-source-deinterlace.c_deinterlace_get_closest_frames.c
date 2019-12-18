#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  void* uint32_t ;
struct video_output_info {scalar_t__ fps_num; scalar_t__ fps_den; } ;
struct TYPE_13__ {TYPE_1__** array; int /*<<< orphan*/  num; } ;
struct TYPE_11__ {int deinterlace_offset; int deinterlace_frame_ts; int last_frame_ts; TYPE_1__* cur_async_frame; void* deinterlace_half_duration; TYPE_1__* prev_async_frame; TYPE_8__ async_frames; scalar_t__ async_unbuffered; } ;
typedef  TYPE_3__ obs_source_t ;
struct TYPE_10__ {int video_time; int /*<<< orphan*/  video; } ;
struct TYPE_12__ {TYPE_2__ video; } ;
struct TYPE_9__ {int timestamp; scalar_t__ prev_frame; } ;

/* Variables and functions */
 int const TS_JUMP_THRESHOLD ; 
 int TWOX_TOLERANCE ; 
 int /*<<< orphan*/  da_erase (TYPE_8__,int /*<<< orphan*/ ) ; 
 scalar_t__ first_frame (TYPE_3__*) ; 
 TYPE_5__* obs ; 
 scalar_t__ ready_deinterlace_frames (TYPE_3__*,int) ; 
 int uint64_diff (int,int) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void deinterlace_get_closest_frames(obs_source_t *s,
						  uint64_t sys_time)
{
	const struct video_output_info *info;
	uint64_t half_interval;

	if (s->async_unbuffered && s->deinterlace_offset) {
		// Want to keep frame if it has not elapsed.
		const uint64_t frame_end =
			s->deinterlace_frame_ts + s->deinterlace_offset +
			((uint64_t)s->deinterlace_half_duration * 2) -
			TWOX_TOLERANCE;
		if (sys_time < frame_end) {
			// Process new frames if we think time jumped.
			const uint64_t diff = frame_end - sys_time;
			if (diff < TS_JUMP_THRESHOLD) {
				return;
			}
		}
	}

	if (!s->async_frames.num)
		return;

	info = video_output_get_info(obs->video.video);
	half_interval = (uint64_t)info->fps_den * 500000000ULL /
			(uint64_t)info->fps_num;

	if (first_frame(s) || ready_deinterlace_frames(s, sys_time)) {
		uint64_t offset;

		s->prev_async_frame = NULL;
		s->cur_async_frame = s->async_frames.array[0];

		da_erase(s->async_frames, 0);

		if (s->cur_async_frame->prev_frame) {
			s->prev_async_frame = s->cur_async_frame;
			s->cur_async_frame = s->async_frames.array[0];

			da_erase(s->async_frames, 0);

			s->deinterlace_half_duration =
				(uint32_t)((s->cur_async_frame->timestamp -
					    s->prev_async_frame->timestamp) /
					   2);
		} else {
			s->deinterlace_half_duration =
				(uint32_t)((s->cur_async_frame->timestamp -
					    s->deinterlace_frame_ts) /
					   2);
		}

		if (!s->last_frame_ts)
			s->last_frame_ts = s->cur_async_frame->timestamp;

		s->deinterlace_frame_ts = s->cur_async_frame->timestamp;

		offset = obs->video.video_time - s->deinterlace_frame_ts;

		if (!s->deinterlace_offset) {
			s->deinterlace_offset = offset;
		} else {
			uint64_t offset_diff =
				uint64_diff(s->deinterlace_offset, offset);
			if (offset_diff > half_interval)
				s->deinterlace_offset = offset;
		}
	}
}