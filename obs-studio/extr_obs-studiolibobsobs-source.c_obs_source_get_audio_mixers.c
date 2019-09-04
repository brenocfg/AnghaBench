#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int output_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  audio_mixers; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_AUDIO ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_2__ const*,char*) ; 

uint32_t obs_source_get_audio_mixers(const obs_source_t *source)
{
	if (!obs_source_valid(source, "obs_source_get_audio_mixers"))
		return 0;
	if ((source->info.output_flags & OBS_SOURCE_AUDIO) == 0)
		return 0;

	return source->audio_mixers;
}