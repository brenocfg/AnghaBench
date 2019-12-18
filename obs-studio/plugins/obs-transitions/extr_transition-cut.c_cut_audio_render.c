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
struct obs_source_audio_mix {int dummy; } ;
struct cut_info {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 int /*<<< orphan*/  mix_a ; 
 int /*<<< orphan*/  mix_b ; 
 int obs_transition_audio_render (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct obs_source_audio_mix*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cut_audio_render(void *data, uint64_t *ts_out,
			     struct obs_source_audio_mix *audio,
			     uint32_t mixers, size_t channels,
			     size_t sample_rate)
{
	struct cut_info *cut = data;
	return obs_transition_audio_render(cut->source, ts_out, audio, mixers,
					   channels, sample_rate, mix_a, mix_b);
}