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
typedef  int uint32_t ;
struct TYPE_2__ {int flags; } ;
struct obs_output {TYPE_1__ info; } ;

/* Variables and functions */
 int OBS_OUTPUT_AUDIO ; 
 int OBS_OUTPUT_ENCODED ; 
 int OBS_OUTPUT_SERVICE ; 
 int OBS_OUTPUT_VIDEO ; 

__attribute__((used)) static inline void convert_flags(const struct obs_output *output,
		uint32_t flags, bool *encoded, bool *has_video, bool *has_audio,
		bool *has_service)
{
	*encoded = (output->info.flags & OBS_OUTPUT_ENCODED) != 0;
	if (!flags)
		flags = output->info.flags;
	else
		flags &= output->info.flags;

	*has_video   = (flags & OBS_OUTPUT_VIDEO)   != 0;
	*has_audio   = (flags & OBS_OUTPUT_AUDIO)   != 0;
	*has_service = (flags & OBS_OUTPUT_SERVICE) != 0;
}