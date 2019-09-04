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
typedef  int pa_sample_format_t ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;

/* Variables and functions */
 int AUDIO_FORMAT_16BIT ; 
 int AUDIO_FORMAT_32BIT ; 
 int AUDIO_FORMAT_FLOAT ; 
 int AUDIO_FORMAT_U8BIT ; 
 int AUDIO_FORMAT_UNKNOWN ; 
#define  PA_SAMPLE_FLOAT32LE 131 
#define  PA_SAMPLE_S16LE 130 
#define  PA_SAMPLE_S32LE 129 
#define  PA_SAMPLE_U8 128 

__attribute__((used)) static enum audio_format pulseaudio_to_obs_audio_format(
		pa_sample_format_t format)
{
	switch (format) {
	case PA_SAMPLE_U8:
		return AUDIO_FORMAT_U8BIT;
	case PA_SAMPLE_S16LE:
		return AUDIO_FORMAT_16BIT;
	case PA_SAMPLE_S32LE:
		return AUDIO_FORMAT_32BIT;
	case PA_SAMPLE_FLOAT32LE:
		return AUDIO_FORMAT_FLOAT;
	default:
		return AUDIO_FORMAT_UNKNOWN;
	}
}