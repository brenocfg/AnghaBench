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
typedef  int uint64_t ;
struct ts_info {void* start; int end; } ;
struct obs_core_audio {int total_buffering_ticks; int buffering_wait_ticks; void* buffered_ts; int /*<<< orphan*/  buffered_timestamps; } ;
typedef  int /*<<< orphan*/  new_ts ;

/* Variables and functions */
 int AUDIO_OUTPUT_FRAMES ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int MAX_BUFFERING_TICKS ; 
 void* audio_frames_to_ns (size_t,int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  circlebuf_push_front (int /*<<< orphan*/ *,struct ts_info*,int) ; 
 int ns_to_audio_frames (size_t,int) ; 

__attribute__((used)) static void add_audio_buffering(struct obs_core_audio *audio,
		size_t sample_rate, struct ts_info *ts, uint64_t min_ts,
		const char *buffering_name)
{
	struct ts_info new_ts;
	uint64_t offset;
	uint64_t frames;
	size_t total_ms;
	size_t ms;
	int ticks;

	if (audio->total_buffering_ticks == MAX_BUFFERING_TICKS)
		return;

	if (!audio->buffering_wait_ticks)
		audio->buffered_ts = ts->start;

	offset = ts->start - min_ts;
	frames = ns_to_audio_frames(sample_rate, offset);
	ticks = (int)((frames + AUDIO_OUTPUT_FRAMES - 1) / AUDIO_OUTPUT_FRAMES);

	audio->total_buffering_ticks += ticks;

	if (audio->total_buffering_ticks >= MAX_BUFFERING_TICKS) {
		ticks -= audio->total_buffering_ticks - MAX_BUFFERING_TICKS;
		audio->total_buffering_ticks = MAX_BUFFERING_TICKS;
		blog(LOG_WARNING, "Max audio buffering reached!");
	}

	ms = ticks * AUDIO_OUTPUT_FRAMES * 1000 / sample_rate;
	total_ms = audio->total_buffering_ticks * AUDIO_OUTPUT_FRAMES * 1000 /
		sample_rate;

	blog(LOG_INFO, "adding %d milliseconds of audio buffering, total "
			"audio buffering is now %d milliseconds"
			" (source: %s)\n",
			(int)ms, (int)total_ms, buffering_name);
#if DEBUG_AUDIO == 1
	blog(LOG_DEBUG, "min_ts (%"PRIu64") < start timestamp "
			"(%"PRIu64")", min_ts, ts->start);
	blog(LOG_DEBUG, "old buffered ts: %"PRIu64"-%"PRIu64,
			ts->start, ts->end);
#endif

	new_ts.start = audio->buffered_ts - audio_frames_to_ns(sample_rate,
			audio->buffering_wait_ticks * AUDIO_OUTPUT_FRAMES);

	while (ticks--) {
		int cur_ticks = ++audio->buffering_wait_ticks;

		new_ts.end = new_ts.start;
		new_ts.start = audio->buffered_ts - audio_frames_to_ns(
				sample_rate,
				cur_ticks * AUDIO_OUTPUT_FRAMES);

#if DEBUG_AUDIO == 1
		blog(LOG_DEBUG, "add buffered ts: %"PRIu64"-%"PRIu64,
				new_ts.start, new_ts.end);
#endif

		circlebuf_push_front(&audio->buffered_timestamps, &new_ts,
				sizeof(new_ts));
	}

	*ts = new_ts;
}