#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct obs_source_audio_mix {TYPE_1__* output; } ;
struct obs_scene_item {struct obs_scene_item* next; int /*<<< orphan*/  source; scalar_t__ visible; } ;
struct obs_scene {struct obs_scene_item* first_item; } ;
struct TYPE_2__ {float** data; } ;

/* Variables and functions */
 size_t AUDIO_OUTPUT_FRAMES ; 
 size_t MAX_AUDIO_MIXES ; 
 int apply_scene_item_volume (struct obs_scene_item*,float**,scalar_t__,size_t) ; 
 int /*<<< orphan*/  audio_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  audio_unlock (struct obs_scene*) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  mix_audio (float*,float*,size_t,size_t) ; 
 int /*<<< orphan*/  mix_audio_with_buf (float*,float*,float*,size_t,size_t) ; 
 scalar_t__ ns_to_audio_frames (size_t,scalar_t__) ; 
 scalar_t__ obs_source_audio_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_get_audio_mix (int /*<<< orphan*/ ,struct obs_source_audio_mix*) ; 
 scalar_t__ obs_source_get_audio_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_all_audio_actions (struct obs_scene_item*,size_t) ; 

__attribute__((used)) static bool scene_audio_render(void *data, uint64_t *ts_out,
			       struct obs_source_audio_mix *audio_output,
			       uint32_t mixers, size_t channels,
			       size_t sample_rate)
{
	uint64_t timestamp = 0;
	float *buf = NULL;
	struct obs_source_audio_mix child_audio;
	struct obs_scene *scene = data;
	struct obs_scene_item *item;

	audio_lock(scene);

	item = scene->first_item;
	while (item) {
		if (!obs_source_audio_pending(item->source) && item->visible) {
			uint64_t source_ts =
				obs_source_get_audio_timestamp(item->source);

			if (source_ts && (!timestamp || source_ts < timestamp))
				timestamp = source_ts;
		}

		item = item->next;
	}

	if (!timestamp) {
		/* just process all pending audio actions if no audio playing,
		 * otherwise audio actions will just never be processed */
		item = scene->first_item;
		while (item) {
			process_all_audio_actions(item, sample_rate);
			item = item->next;
		}

		audio_unlock(scene);
		return false;
	}

	item = scene->first_item;
	while (item) {
		uint64_t source_ts;
		size_t pos, count;
		bool apply_buf;

		apply_buf = apply_scene_item_volume(item, &buf, timestamp,
						    sample_rate);

		if (obs_source_audio_pending(item->source)) {
			item = item->next;
			continue;
		}

		source_ts = obs_source_get_audio_timestamp(item->source);
		if (!source_ts) {
			item = item->next;
			continue;
		}

		pos = (size_t)ns_to_audio_frames(sample_rate,
						 source_ts - timestamp);
		count = AUDIO_OUTPUT_FRAMES - pos;

		if (!apply_buf && !item->visible) {
			item = item->next;
			continue;
		}

		obs_source_get_audio_mix(item->source, &child_audio);
		for (size_t mix = 0; mix < MAX_AUDIO_MIXES; mix++) {
			if ((mixers & (1 << mix)) == 0)
				continue;

			for (size_t ch = 0; ch < channels; ch++) {
				float *out = audio_output->output[mix].data[ch];
				float *in = child_audio.output[mix].data[ch];

				if (apply_buf)
					mix_audio_with_buf(out, in, buf, pos,
							   count);
				else
					mix_audio(out, in, pos, count);
			}
		}

		item = item->next;
	}

	*ts_out = timestamp;
	audio_unlock(scene);

	free(buf);
	return true;
}