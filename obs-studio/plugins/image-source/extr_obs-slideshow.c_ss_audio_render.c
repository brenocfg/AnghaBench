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
typedef  int /*<<< orphan*/  uint32_t ;
struct slideshow {int dummy; } ;
struct obs_source_audio_mix {int dummy; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * get_transition (struct slideshow*) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int ss_audio_render_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct obs_source_audio_mix*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static bool ss_audio_render(void *data, uint64_t *ts_out,
			    struct obs_source_audio_mix *audio_output,
			    uint32_t mixers, size_t channels,
			    size_t sample_rate)
{
	struct slideshow *ss = data;
	obs_source_t *transition = get_transition(ss);
	bool success;

	if (!transition)
		return false;

	success = ss_audio_render_(transition, ts_out, audio_output, mixers,
				   channels, sample_rate);

	obs_source_release(transition);
	return success;
}