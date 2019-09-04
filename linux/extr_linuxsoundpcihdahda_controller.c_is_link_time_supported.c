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
struct TYPE_2__ {int info; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct snd_pcm_audio_tstamp_config {scalar_t__ type_requested; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED ; 
 int SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME ; 

__attribute__((used)) static inline bool is_link_time_supported(struct snd_pcm_runtime *runtime,
				struct snd_pcm_audio_tstamp_config *ts)
{
	if (runtime->hw.info & SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME)
		if (ts->type_requested == SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED)
			return true;

	return false;
}