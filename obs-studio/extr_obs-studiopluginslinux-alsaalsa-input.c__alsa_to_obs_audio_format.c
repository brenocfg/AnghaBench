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
typedef  int snd_pcm_format_t ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;

/* Variables and functions */
 int AUDIO_FORMAT_16BIT ; 
 int AUDIO_FORMAT_32BIT ; 
 int AUDIO_FORMAT_FLOAT ; 
 int AUDIO_FORMAT_U8BIT ; 
 int AUDIO_FORMAT_UNKNOWN ; 
#define  SND_PCM_FORMAT_FLOAT_LE 131 
#define  SND_PCM_FORMAT_S16_LE 130 
#define  SND_PCM_FORMAT_S32_LE 129 
#define  SND_PCM_FORMAT_U8 128 

enum audio_format _alsa_to_obs_audio_format(snd_pcm_format_t format)
{
	switch (format) {
	case SND_PCM_FORMAT_U8:       return AUDIO_FORMAT_U8BIT;
	case SND_PCM_FORMAT_S16_LE:   return AUDIO_FORMAT_16BIT;
	case SND_PCM_FORMAT_S32_LE:   return AUDIO_FORMAT_32BIT;
	case SND_PCM_FORMAT_FLOAT_LE: return AUDIO_FORMAT_FLOAT;
	default:                      break;
	}

	return AUDIO_FORMAT_UNKNOWN;
}