#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ts_info {int end; int start; } ;
struct obs_core_audio {scalar_t__ total_buffering_ticks; } ;
struct TYPE_7__ {scalar_t__ audio_render; } ;
struct TYPE_8__ {int audio_ts; int pending_stop; scalar_t__ last_audio_input_buf_size; TYPE_6__* audio_input_buf; scalar_t__ audio_pending; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;
struct TYPE_9__ {size_t size; } ;

/* Variables and functions */
 size_t AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_SIZE ; 
 scalar_t__ MAX_BUFFERING_TICKS ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_6__*,int /*<<< orphan*/ *,size_t) ; 
 size_t convert_time_to_frames (size_t,int) ; 
 scalar_t__ discard_if_stopped (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ignore_audio (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static inline void discard_audio(struct obs_core_audio *audio,
		obs_source_t *source, size_t channels, size_t sample_rate,
		struct ts_info *ts)
{
	size_t total_floats = AUDIO_OUTPUT_FRAMES;
	size_t size;

#if DEBUG_AUDIO == 1
	bool is_audio_source = source->info.output_flags & OBS_SOURCE_AUDIO;
#endif

	if (source->info.audio_render) {
		source->audio_ts = 0;
		return;
	}

	if (ts->end <= source->audio_ts) {
#if DEBUG_AUDIO == 1
		blog(LOG_DEBUG, "can't discard, source "
				"timestamp (%"PRIu64") >= "
				"end timestamp (%"PRIu64")",
				source->audio_ts, ts->end);
#endif
		return;
	}

	if (source->audio_ts < (ts->start - 1)) {
		if (source->audio_pending &&
		    source->audio_input_buf[0].size < MAX_AUDIO_SIZE &&
		    discard_if_stopped(source, channels))
			return;

#if DEBUG_AUDIO == 1
		if (is_audio_source) {
			blog(LOG_DEBUG, "can't discard, source "
					"timestamp (%"PRIu64") < "
					"start timestamp (%"PRIu64")",
					source->audio_ts, ts->start);
		}
#endif
		if (audio->total_buffering_ticks == MAX_BUFFERING_TICKS)
			ignore_audio(source, channels, sample_rate);
		return;
	}

	if (source->audio_ts != ts->start &&
	    source->audio_ts != (ts->start - 1)) {
		size_t start_point = convert_time_to_frames(sample_rate,
				source->audio_ts - ts->start);
		if (start_point == AUDIO_OUTPUT_FRAMES) {
#if DEBUG_AUDIO == 1
			if (is_audio_source)
				blog(LOG_DEBUG, "can't discard, start point is "
						"at audio frame count");
#endif
			return;
		}

		total_floats -= start_point;
	}

	size = total_floats * sizeof(float);

	if (source->audio_input_buf[0].size < size) {
		if (discard_if_stopped(source, channels))
			return;

#if DEBUG_AUDIO == 1
		if (is_audio_source)
			blog(LOG_DEBUG, "can't discard, data still pending");
#endif
		return;
	}

	for (size_t ch = 0; ch < channels; ch++)
		circlebuf_pop_front(&source->audio_input_buf[ch], NULL, size);

	source->last_audio_input_buf_size = 0;

#if DEBUG_AUDIO == 1
	if (is_audio_source)
		blog(LOG_DEBUG, "audio discarded, new ts: %"PRIu64,
				ts->end);
#endif

	source->pending_stop = false;
	source->audio_ts = ts->end;
}