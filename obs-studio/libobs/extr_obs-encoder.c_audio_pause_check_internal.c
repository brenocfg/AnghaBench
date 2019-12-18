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
typedef  scalar_t__ uint64_t ;
struct pause_data {scalar_t__ ts_start; scalar_t__ ts_end; } ;
struct audio_data {scalar_t__ timestamp; int /*<<< orphan*/  frames; } ;

/* Variables and functions */
 scalar_t__ audio_frames_to_ns (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_audio (struct pause_data*,struct audio_data*,size_t) ; 
 int /*<<< orphan*/  unpause_audio (struct pause_data*,struct audio_data*,size_t) ; 

__attribute__((used)) static inline bool audio_pause_check_internal(struct pause_data *pause,
					      struct audio_data *data,
					      size_t sample_rate)
{
	uint64_t end_ts;

	if (!pause->ts_start) {
		return false;
	}

	end_ts =
		data->timestamp + audio_frames_to_ns(sample_rate, data->frames);

	if (pause->ts_start >= data->timestamp) {
		if (pause->ts_start <= end_ts) {
			pause_audio(pause, data, sample_rate);
			return !data->frames;
		}

	} else {
		if (pause->ts_end >= data->timestamp &&
		    pause->ts_end <= end_ts) {
			unpause_audio(pause, data, sample_rate);
			return !data->frames;
		}

		return true;
	}

	return false;
}