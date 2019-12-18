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
typedef  int /*<<< orphan*/  uint64_t ;
struct obs_source {scalar_t__ next_audio_source; } ;
struct obs_core_data {struct obs_source* first_audio_source; } ;

/* Variables and functions */
 int audio_buffer_insuffient (struct obs_source*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mark_invalid_sources(struct obs_core_data *data,
					size_t sample_rate, uint64_t min_ts)
{
	bool recalculate = false;

	struct obs_source *source = data->first_audio_source;
	while (source) {
		recalculate |=
			audio_buffer_insuffient(source, sample_rate, min_ts);
		source = (struct obs_source *)source->next_audio_source;
	}

	return recalculate;
}