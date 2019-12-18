#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ raw_audio2; } ;
struct TYPE_8__ {size_t mixer_mask; int /*<<< orphan*/  audio; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_output_t ;

/* Variables and functions */
 int MAX_AUDIO_MIXES ; 
 int /*<<< orphan*/  audio_output_connect (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  default_raw_audio_callback ; 
 int /*<<< orphan*/  get_audio_conversion (TYPE_2__*) ; 
 int get_first_mixer (TYPE_2__*) ; 

__attribute__((used)) static inline void start_raw_audio(obs_output_t *output)
{
	if (output->info.raw_audio2) {
		for (int idx = 0; idx < MAX_AUDIO_MIXES; idx++) {
			if ((output->mixer_mask & ((size_t)1 << idx)) != 0) {
				audio_output_connect(
					output->audio, idx,
					get_audio_conversion(output),
					default_raw_audio_callback, output);
			}
		}
	} else {
		audio_output_connect(output->audio, get_first_mixer(output),
				     get_audio_conversion(output),
				     default_raw_audio_callback, output);
	}
}